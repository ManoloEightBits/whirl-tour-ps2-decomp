#include "common/types.h"

// Functions of 0x001A8000..0x001ABFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001A6780(); // 0x001A6780
void func_001AB8C8(); // 0x001AB8C8

u32 func_001A9370(int arg0)
{
    return (u32) (arg0 << 0xC) / 48000U;
}

int func_001AB370()
{
    func_001AB8C8();
    return 0;
}

void func_001ABD60()
{
    func_001A6780();
}

int func_001ABE88()
{
    return 0;
}

// UnkObj1A9768 (0x001A9768): no RTTI; its layout is the fields these methods use.
struct UnkObj1A9768
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    int GetField8();     // 0x001A9768
};

int UnkObj1A9768::GetField8()
{
    return mField8;
}

extern "C" int printf(const char *, ...);

void func_001AA4B0()
{
    printf("ERROR: SOUND_SetDTSMode\n");
    func_001AB8C8();
}

void func_001AB430()
{
    printf("ERROR: SOUND_CreateDTS_RPCThread\n");
    func_001AB8C8();
}

void func_001ABE60()
{
    printf("ERROR: SOUND_DTS_Thread\n");
    func_001AB8C8();
}

extern int data_002795B0;
extern int data_002795B4;

void func_001AA1C0(s16 arg0)
{
    if (data_002795B4 != -1)
    {
        printf(">>>>> ERROR: SOUND_StartCommand\n");
        printf("Previous command (%d) not completed\n", data_002795B4);
        printf("To complete a command, it must end with SOUND_EndCommand\n");
        return;
    }
    data_002795B4 = (int)arg0;
    data_002795B0 = 0;
}

int func_001AA6C0()
{
    printf("ERROR: SOUND_GetDTSStatus\n");
    func_001AB8C8();
    return 0;
}

void func_001AB8C8()
{
    printf("ERROR: SOUND_Init_EE_DTS\n");
    printf("DTS not enabled. Set SOUND_DTS_ENABLE to 1 (in Sound.C)\n");
    printf("The DTS encode routine that you are attempting to call\n");
    printf("is a propriety technology. In order to utilize this\n");
    printf("technology a licensing agreement is required.\n");
    printf("The DTS SDK can be obtained from DTS.\n");
}
