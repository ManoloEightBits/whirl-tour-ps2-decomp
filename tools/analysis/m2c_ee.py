#!/usr/bin/env python3
"""m2c with two fixes for the game's code, as a module (patch()) and as a command (same arguments as m2c).

Usage:
  m2c_ee.py <m2c arguments>       # e.g. -t mipsee-gcc-c --valid-syntax func.s

1. The address of the stack slot at offset 0. ee-gcc writes it as `daddu $a1, $sp, $zero` (or
   `addiu $a1, $sp, 0`), and m2c turns both into `move $a1, $sp` before it looks for the address of a
   local variable: the slot then counts as outgoing arguments and the draft passes a bare `sp`. With
   the patch the instruction stays `addiu $a1, $sp, 0` and the draft reads `&sp0`. (Copies into the
   frame pointer stay moves: m2c needs them to find the frame.)

2. Addresses of globals (see symbolize() in inspect_tu.py, which prepares the input): m2c only knows
   a global through `lui $r, %hi(sym)`, and it then takes the register for the whole address of sym
   (it ignores what is inside a later %lo). symbolize() names the first address built from each lui and
   writes the other loads and stores through that register as offsets from it, which is how m2c reads
   them; with raw addresses the draft has untyped expressions like `*(0x25E168 + (arg0 * 4))`.
"""
import sys


def patch():
    """Apply fix 1 to m2c's MIPS EE target (idempotent)."""
    from m2c.arch_mips import MipseeArch
    from m2c.asm_instruction import AsmInstruction, AsmLiteral, Register

    if getattr(MipseeArch, '_whirl_patched', False):
        return
    original = MipseeArch.normalize_instruction.__func__
    sp = Register('sp')
    keep_move = {Register('sp'), Register('fp'), Register('s8')}

    def normalize_instruction(cls, instr, asm_state):
        a = instr.args
        if len(a) == 3 and a[1] == sp and a[0] not in keep_move and (
                (instr.mnemonic in ('addu', 'daddu', 'or') and a[2] == Register('zero'))
                or (instr.mnemonic in ('addiu', 'daddiu') and a[2] == AsmLiteral(0))):
            return AsmInstruction('addiu', [a[0], sp, AsmLiteral(0)])
        return original(cls, instr, asm_state)

    MipseeArch.normalize_instruction = classmethod(normalize_instruction)

    # handle_addi returns the source unchanged for "+ 0" before it checks for a stack address.
    from m2c import evaluate
    from m2c.translate import Literal
    original_addi = evaluate.handle_addi

    def handle_addi(output_reg, source_reg, source, imm, args):
        if imm == Literal(0) and args.stack_info.is_stack_reg(source_reg) \
                and not args.stack_info.is_stack_reg(output_reg):
            return evaluate.handle_addi_real(output_reg, source_reg, source, imm, args)
        return original_addi(output_reg, source_reg, source, imm, args)

    evaluate.handle_addi = handle_addi
    MipseeArch._whirl_patched = True


def main():
    patch()
    from m2c.main import main as m2c_main
    sys.argv[0] = 'm2c'
    return m2c_main()


if __name__ == '__main__':
    sys.exit(main())
