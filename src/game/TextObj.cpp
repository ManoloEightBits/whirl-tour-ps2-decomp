#include "game/FEScreen.h"

// TextObj: the lines of text the front end draws (0x00198E48..0x00198F58). They come from the
// game's allocator (MemAlloc1BD958), not from __builtin_new.

void *MemAlloc1BD958(int size); // 0x001BD958
void MemFree1BD978(void *p);    // 0x001BD978

TextObj *CreateTextObj198E48(void *font, const char *str, f32 x, f32 y, f32 z)
{
    TextObj *text = (TextObj *)MemAlloc1BD958(sizeof(TextObj));
    if (text != 0)
        text->Init(font, str, x, y, z);
    return text;
}

void TextObj::Init(void *font, const char *str, f32 x, f32 y, f32 z)
{
    mPos04.Set(x, y, z);
    mFont2C = font;
    mString30 = str;
    mAlign00 = 0;
    mPos04.Set(x, y, z);
    TEXT_SET_RGBA(this, 0x80808080);
    mOffset10.Set(0.0f, 0.0f, 0.0f);
    mScale1C.Set(1.0f, 1.0f, 1.0f);
    mWidth34 = 0.0f;
}

void Release198F38(void *text)
{
    MemFree1BD978(text);
}

void DrawText19B758(TextObj *text)
{
    DrawTextEx19B2C0(text, 0.0f);
}

void DrawText19B778(TextObj *text, f32 arg)
{
    DrawTextEx19B2C0(text, arg);
}
