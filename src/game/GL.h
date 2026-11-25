#ifndef WHIRL_TOUR_GAME_GL_H
#define WHIRL_TOUR_GAME_GL_H

/* The game's OpenGL-style render layer (0x0019F000..0x001A5000). Its functions take OpenGL enum values,
   and glEnable/glDisable are a switch over capabilities that set or clear one flag each in the render
   state at 0x00277140 (glEnable(GL_SCISSOR_TEST) also reloads the scissor box). The enum values are
   OpenGL's. */

#define GL_TRIANGLE_STRIP      0x0005
#define GL_FOG                 0x0B60
#define GL_LIGHTING            0x0B50
#define GL_CULL_FACE           0x0B44
#define GL_DEPTH_TEST          0x0B71
#define GL_ALPHA_TEST          0x0BC0
#define GL_BLEND               0x0BE2
#define GL_SCISSOR_TEST        0x0C11
#define GL_TEXTURE_2D          0x0DE1
#define GL_UNSIGNED_BYTE       0x1401
#define GL_FLOAT               0x1406
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_VERTEX_ARRAY        0x8074
#define GL_COLOR_ARRAY         0x8076
#define GL_TEXTURE_COORD_ARRAY 0x8078

/* The *Pointer functions keep the size and the pointer (not the type or stride) in the array state at
   0x00267140; glDrawArrays reads them back. glBindTexture looks the name up in the texture table. */
extern "C" {
void glDrawArrays(unsigned int mode, int first, int count);                         /* 0x001A1938 */
void glBindTexture(unsigned int target, unsigned int texture);                      /* 0x001A2340 */
void glEnable(unsigned int cap);                                                    /* 0x001A2DB8 */
void glDisable(unsigned int cap);                                                   /* 0x001A2FB8 */
void glTexCoordPointer(int size, unsigned int type, int stride, const void *ptr);   /* 0x001A43C8 */
void glVertexPointer(int size, unsigned int type, int stride, const void *ptr);     /* 0x001A43E0 */
void glColorPointer(int size, unsigned int type, int stride, const void *ptr);      /* 0x001A43F8 */
void glEnableClientState(unsigned int array);                                       /* 0x001A4410 */
void glDisableClientState(unsigned int array);                                      /* 0x001A4490 */
}

#endif /* WHIRL_TOUR_GAME_GL_H */
