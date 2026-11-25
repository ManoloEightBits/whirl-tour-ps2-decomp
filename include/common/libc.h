#ifndef WHIRL_TOUR_COMMON_LIBC_H
#define WHIRL_TOUR_COMMON_LIBC_H

/* The newlib C library functions the game calls. They live in the runtime region (not decompiled) and
   were identified from their code: each reads newlib's _impure_ptr (0x0027D60C) or is one of Sony's
   128-bit EE string/memory routines. C linkage, as in <stdio.h>, <stdlib.h> and <string.h>. */
extern "C" {
void *malloc(unsigned int size);                          /* 0x0022E8E0: _malloc_r(_impure_ptr, size) */
void *memcpy(void *dst, const void *src, unsigned int n); /* 0x0022F45C: 32/8/1-byte copy loops */
void *memset(void *dst, int c, unsigned int n);           /* 0x0022F50C: 32/8/1-byte fill loops */
int printf(const char *fmt, ...);                         /* 0x0022FC78: vfprintf(_stdout, fmt, ap) */
int rand(void);                                           /* 0x00230700: seed * 1103515245 + 12345 */
int sprintf(char *buf, const char *fmt, ...);            /* 0x00231300: vfprintf to a string FILE, then the 0 */
int strcmp(const char *a, const char *b);                 /* 0x002317B4: returns (u8)*a - (u8)*b */
}

#endif /* WHIRL_TOUR_COMMON_LIBC_H */
