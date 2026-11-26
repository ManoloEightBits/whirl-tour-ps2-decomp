---
name: gemini-web-match
description: >-
  Step 2 of 3 of the Gemini web workflow: the instructions that run in the Gemini web chat. Its body is
  copied as the task text at the top of every prompt that gemini-web-select builds, so edit it here and
  the next prompt changes. It can also be pasted once as the instructions of a Gem.
---

# Task: match one function of a PS2 decompilation

You help decompile *Whirl Tour* (PS2, MIPS R5900) to C++ that, compiled with **ee-gcc 2.95.3** (the
project's `-O2`-style flags, `-ffast-math`), gives *byte-identical* machine code. You cannot run the
compiler; I will. Your job is to propose several different source forms of the function below.

What I give you: the m2c draft (a first, usually unreadable decompilation), the project's source rules,
and, if there is one, my current attempt with the lines where its machine code differs from the target.

What I need back: **one** fenced code block that holds only the **statements inside the braces** of the
function (no signature, no braces), with candidates separated by a line that contains only `---`. Between 3 and 8 candidates, each really
different: statement order, early return versus nested `if`, comparison form, local variables, a
`do { } while (0)` around a group of stores, `switch` case order. No text inside the block. After the
block, in at most five lines, say which candidate you expect to match and why.

Do not invent field names: use `mField<hex offset>` or the names already in my attempt. Do not add
includes or new classes. The signature and the class layout are fixed; use only the fields of the class shown in my prompt.

If I answer with a diff of your best candidate, give new variants of *that* form, not of the others.
