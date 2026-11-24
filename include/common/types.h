#ifndef WHIRL_TOUR_COMMON_TYPES_H
#define WHIRL_TOUR_COMMON_TYPES_H

/* Fixed-width Emotion Engine (MIPS R5900) base types for GCC 2.95.3 */
typedef signed char        s8;
typedef unsigned char      u8;
typedef signed short       s16;
typedef unsigned short     u16;
typedef signed int         s32;
typedef unsigned int       u32;
typedef signed long        s64;
typedef unsigned long      u64;
typedef float              f32;
typedef double             f64;

#ifndef NULL
#define NULL 0
#endif

#define STATIC_ASSERT(cond, name) typedef char static_assert_##name[(cond) ? 1 : -1]

struct Vec3f {
    f32 x; /* 0x00 */
    f32 y; /* 0x04 */
    f32 z; /* 0x08 */
};

struct Vec4f {
    f32 x; /* 0x00 */
    f32 y; /* 0x04 */
    f32 z; /* 0x08 */
    f32 w; /* 0x0C */
};

struct Mat4x4f {
    Vec4f row[4]; /* 0x00..0x3F */
};

#endif /* WHIRL_TOUR_COMMON_TYPES_H */
