#include "common/types.h"

// Functions of 0x00160000..0x00163FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00163698(); // 0x00163698

void func_00163A30()
{
    func_00163698();
}
