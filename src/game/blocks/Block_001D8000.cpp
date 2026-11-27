#include "common/types.h"

// Functions of 0x001D8000..0x001DBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001D8270(int arg0)
{
    return arg0 + 0x40;
}

int func_001D8280(int arg0)
{
    return arg0 + 0x20;
}

int func_001D8288(int arg0)
{
    return arg0 + 0x40;
}

int func_001D82F0(int *arg0)
{
    return *arg0 & 3;
}

int func_001D8390(int arg0)
{
    return arg0 + 0x100;
}

int func_001D8398(int arg0)
{
    return arg0 + 0x130;
}

int func_001DBB68(int arg0)
{
    return arg0;
}

int func_001DBCE8(int arg0)
{
    return arg0 + 0x34;
}

int func_001DBD40(int arg0)
{
    return arg0 + 0xC0;
}

int func_001DBD20(int arg0)
{
    return arg0 + 0x88;
}

struct UnkObj1DBC18
{
    f32 GetField12C();                  // 0x001DBC18
    f32 GetFieldAC();                   // 0x001DBC50
    f32 GetFieldB0();                   // 0x001DBC58
    int GetField11C();                  // 0x001DBC60
    int GetField128();                  // 0x001DBC68
    int GetField4();                    // 0x001DBC70
    int GetField90();                   // 0x001DBC78
    int GetField10();                   // 0x001DBC80
    int GetField8();                    // 0x001DBC88
    int GetField94();                   // 0x001DBC90
    int GetField14();                   // 0x001DBC98
    int GetFieldC();                    // 0x001DBCA0
    int GetField140();                  // 0x001DBCA8
    int GetFieldA0();                   // 0x001DBCB0
    int GetField28();                   // 0x001DBCB8
    int GetFieldA4();                   // 0x001DBCC0
    int GetFieldA0b();                  // 0x001DBCC8
    int GetField1C();                   // 0x001DBCD0
    int GetField9C();                   // 0x001DBCD8
    int GetField18();                   // 0x001DBCE0
    int GetField8C();                   // 0x001DBCF0
    int GetField98();                   // 0x001DBCF8
    int GetField2C();                   // 0x001DBD00
    int GetField20();                   // 0x001DBD08
    int GetField24();                   // 0x001DBD10
    int GetField30();                   // 0x001DBD18

    char field_0x0[0x4];
    int mField4;              // 0x4
    int mField8;              // 0x8
    int mFieldC;              // 0xC
    int mField10;             // 0x10
    int mField14;             // 0x14
    int mField18;             // 0x18
    int mField1C;             // 0x1C
    int mField20;             // 0x20
    int mField24;             // 0x24
    int mField28;             // 0x28
    int mField2C;             // 0x2C
    int mField30;             // 0x30
    char field_0x34[0x58];
    int mField8C;             // 0x8C
    int mField90;             // 0x90
    int mField94;             // 0x94
    int mField98;             // 0x98
    int mField9C;             // 0x9C
    int mFieldA0;             // 0xA0
    int mFieldA4;             // 0xA4
    char field_0xA8[0x4];
    f32 mFieldAC;             // 0xAC
    f32 mFieldB0;             // 0xB0
    char field_0xB4[0x68];
    int mField11C;            // 0x11C
    char field_0x120[0x8];
    int mField128;            // 0x128
    f32 mField12C;            // 0x12C
    char field_0x130[0x10];
    int mField140;            // 0x140
};

f32 UnkObj1DBC18::GetField12C() { return mField12C; }
f32 UnkObj1DBC18::GetFieldAC() { return mFieldAC; }
f32 UnkObj1DBC18::GetFieldB0() { return mFieldB0; }
int UnkObj1DBC18::GetField11C() { return mField11C; }
int UnkObj1DBC18::GetField128() { return mField128; }
int UnkObj1DBC18::GetField4() { return mField4; }
int UnkObj1DBC18::GetField90() { return mField90; }
int UnkObj1DBC18::GetField10() { return mField10; }
int UnkObj1DBC18::GetField8() { return mField8; }
int UnkObj1DBC18::GetField94() { return mField94; }
int UnkObj1DBC18::GetField14() { return mField14; }
int UnkObj1DBC18::GetFieldC() { return mFieldC; }
int UnkObj1DBC18::GetField140() { return mField140; }
int UnkObj1DBC18::GetFieldA0() { return mFieldA0; }
int UnkObj1DBC18::GetField28() { return mField28; }
int UnkObj1DBC18::GetFieldA4() { return mFieldA4; }
int UnkObj1DBC18::GetFieldA0b() { return mFieldA0; }
int UnkObj1DBC18::GetField1C() { return mField1C; }
int UnkObj1DBC18::GetField9C() { return mField9C; }
int UnkObj1DBC18::GetField18() { return mField18; }
int UnkObj1DBC18::GetField8C() { return mField8C; }
int UnkObj1DBC18::GetField98() { return mField98; }
int UnkObj1DBC18::GetField2C() { return mField2C; }
int UnkObj1DBC18::GetField20() { return mField20; }
int UnkObj1DBC18::GetField24() { return mField24; }
int UnkObj1DBC18::GetField30() { return mField30; }

