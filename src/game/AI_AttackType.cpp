// Whirl Tour: AI_AttackType RTTI function (__tf), proves compiler/flags (SN ee-gcc 2.95.3 b1.14, -O2 -G0).
class EnvObj
{
public:
    virtual void Dummy();
};

class AI_AttackType : public EnvObj
{
public:
    AI_AttackType();
    virtual void V1() = 0;
    virtual void V2() = 0;
    virtual void V3() = 0;
    virtual void V4() = 0;
    virtual void V5() = 0;
    virtual void V6() = 0;
    virtual void V7() = 0;
};

// The game has no out-of-line constructor; the ctor exists here only to make the compiler emit the
// vtable and __tf. verify.py reports it as 'not in symbols.txt', which is expected for this probe.
AI_AttackType::AI_AttackType()
{
}
