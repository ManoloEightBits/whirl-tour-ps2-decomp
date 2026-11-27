#include "common/libc.h"
#include "game/FEScreen.h"
#include "game/GL.h"

// TextObj: the lines of text the front end draws (0x00198E48..0x00198F58). They come from the
// game's allocator (MemAlloc1BD958), not from __builtin_new.

void *MemAlloc1BD958(int size); // 0x001BD958
void MemFree1BD978(void *p);    // 0x001BD978
void func_00199858(int count, int alignBits, void **outPtr); // 0x00199858
extern "C" f32 func_001BACA8(void *, int); // 0x001BACA8
extern "C" void func_001BAD18(void *, int, void *); // 0x001BAD18

extern f32 data_00265D00;
extern f32 data_00265D04;

struct UnkTex1BA
{
    int GetField18(); // 0x001BAA90
};

struct UnkFont19B2C0
{
    int mField00;       // 0x00
    f32 mField04;       // 0x04
    UnkTex1BA *mTex08;  // 0x08
};

struct UnkGlyph19B2C0
{
    u32 mTex; // 0x00
    f32 mW;   // 0x04
    f32 mH;   // 0x08
    void *mUV; // 0x0C
};

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

#ifdef NON_MATCHING
// 209/296 diffs: prologue/strlen/MeasureText19B138/GetField18/switch-binary-tree/loop structure match;
// remaining differences are Vec3f pos/offset pointer CSE, constant hoisting (0xA in $s4, "%x" in $s5),
// and vertex-store / glDrawArrays scheduling.
void DrawTextEx19B2C0(TextObj *text, f32 maxWidth)
{
    const u8 *str = (const u8 *)text->mString30;
    UnkFont19B2C0 *font = (UnkFont19B2C0 *)text->mFont2C;
    if (str != 0 && font != 0 && strlen((const char *)str) != 0)
    {
        MeasureText19B138(text);
        f32 lineH = font->mField04 * (f32)((UnkFont19B2C0 *)text->mFont2C)->mTex08->GetField18() * data_00265D04 * text->mScale1C.y;
        f32 z = text->mPos04.z - text->mOffset10.z;
        f32 startX = text->mPos04.x - text->mOffset10.x;
        f32 y = text->mPos04.y - text->mOffset10.y;
        switch (text->mAlign00 & 0xF)
        {
        case 0:
            break;
        case 1:
            startX -= text->mWidth34;
            break;
        case 2:
            startX += text->mWidth34 * -0.5f;
            break;
        case 3:
            break;
        }
        switch (text->mAlign00 & 0xF0)
        {
        case 0:
            break;
        case 0x10:
            y += text->mHeight38;
            break;
        case 0x20:
            y += text->mHeight38 * 0.5f;
            break;
        case 0x30:
            break;
        }
        glEnable(0xDE1);
        f32 x = startX;
        glDisable(0xB44);
        glEnable(0xBE2);
        glBlendFunc(0x302, 0x303);
        glDepthMask(0);
        glColor4ubv((const u8 *)&text->mColor28);
        glEnableClientState(0x8074);
        glEnableClientState(0x8078);
        const u8 *p = str;
        while (*p != 0)
        {
            u32 ch = *p++;
            if (ch == 0x80)
                ch = (*p++) | 0x8000;
            if (ch == '\\')
            {
                ch = *p++;
                if (ch == 'n')
                    ch = '\n';
                if (ch == 'c')
                {
                    p++;
                    u32 rgba;
                    if (sscanf((const char *)p, "%x", &rgba) == 1)
                    {
                        u32 color = ((((rgba >> 24) & 0xFF) + 1) >> 1)
                                  | (((((rgba >> 16) & 0xFF) + 1) >> 1) << 8)
                                  | (((((rgba >> 8) & 0xFF) + 1) >> 1) << 16)
                                  | (((((rgba & 0xFF) + 1) >> 1)) << 24);
                        glColor4ubv((const u8 *)&color);
                        while (*p++ != '}')
                            ;
                        continue;
                    }
                }
            }
            if (ch == '\n')
            {
                x = startX;
                y -= lineH;
            }
            else if (ch == ' ')
            {
                x += func_001BACA8(text->mFont2C, ' ') * data_00265D00 * text->mScale1C.x;
            }
            else
            {
                UnkGlyph19B2C0 glyph;
                func_001BAD18(text->mFont2C, ch, &glyph);
                f32 gw = glyph.mW * data_00265D00 * text->mScale1C.x;
                f32 gh = glyph.mH * data_00265D00 * text->mScale1C.x;
                glBindTexture(0xDE1, glyph.mTex);
                Vec3f *verts;
                func_00199858(6, 6, (void **)&verts);
                glVertexPointer(3, 0x1406, 0, verts);
                glTexCoordPointer(2, 0x1406, 0, glyph.mUV);
                f32 y0 = y - lineH;
                f32 x1 = x + gw;
                verts[0].x = x;
                verts[0].z = z;
                verts[0].y = y;
                do { Vec3f *v = &verts[1]; v->x = x; v->z = z; v->y = y0; } while (0);
                do { Vec3f *v = &verts[2]; v->x = x1; v->z = z; v->y = y; } while (0);
                do { Vec3f *v = &verts[3]; v->x = x; v->z = z; v->y = y0; } while (0);
                do { Vec3f *v = &verts[4]; v->x = x1; v->z = z; v->y = y0; } while (0);
                do { Vec3f *v = &verts[5]; v->x = x1; v->z = z; v->y = y; } while (0);
                x += gh;
                glDrawArrays(4, 0, 6);
            }
            if (maxWidth > 0.0f && maxWidth < x - startX)
                break;
        }
        glDisableClientState(0x8074);
        glDisableClientState(0x8078);
        glBlendFunc(0x302, 0x303);
        glDisable(0xBE2);
        glDisable(0xDE1);
        glEnable(0xB44);
        glDepthMask(1);
    }
}
#endif
