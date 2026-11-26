#ifndef WHIRL_TOUR_GAME_GL_H
#define WHIRL_TOUR_GAME_GL_H

#include "common/types.h"

/* The game's OpenGL-style render layer (0x0019F000..0x001A5000). Its functions take OpenGL enum values,
   and glEnable/glDisable are a switch over capabilities that set or clear one flag each in the render
   state at 0x00277140 (glEnable(GL_SCISSOR_TEST) also reloads the scissor box). The enum values are
   OpenGL's. */

#define GL_TRIANGLE_STRIP      0x0005
#define GL_SRC_ALPHA           0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_FOG                 0x0B60
#define GL_LIGHTING            0x0B50
#define GL_LIGHT_MODEL_AMBIENT 0x0B53
#define GL_CULL_FACE           0x0B44
#define GL_DEPTH_TEST          0x0B71
#define GL_ALPHA_TEST          0x0BC0
#define GL_BLEND               0x0BE2
#define GL_SCISSOR_TEST        0x0C11
#define GL_VIEWPORT            0x0BA2
#define GL_TEXTURE_2D          0x0DE1
#define GL_UNSIGNED_BYTE       0x1401
#define GL_FLOAT               0x1406
#define GL_MODELVIEW           0x1700
#define GL_PROJECTION          0x1701
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_VERTEX_ARRAY        0x8074
#define GL_COLOR_ARRAY         0x8076
#define GL_TEXTURE_COORD_ARRAY 0x8078
#define GL_LIGHT0              0x4000
#define GL_LIGHT1              0x4001
#define GL_LIGHT2              0x4002

/* Immediate mode: glBegin starts a primitive in the vertex buffer (0x002670A0), glVertex3f appends a
   0x30-byte vertex with the current texture coordinate and colour (glTexCoord2f, glColor3f/4f; colours
   are kept scaled to the GS range 0..128) and glEnd sends it. glPushMatrix/glPopMatrix move the stack
   of the mode glMatrixMode chose (GL_MODELVIEW or GL_PROJECTION) by one 0x40-byte matrix, and
   glRotatef (a quaternion from the half angle in radians), glTranslatef and glMultMatrixf multiply into
   its top.
   The *Pointer functions keep the size and the pointer (not the type or stride) in the array state at
   0x00267140; glDrawArrays reads them back. glBindTexture looks the name up in the texture table. */
extern "C" {
void glEnd(void);                                                                   /* 0x001A1418 */
void glDrawArrays(unsigned int mode, int first, int count);                         /* 0x001A1938 */
void glBindTexture(unsigned int target, unsigned int texture);                      /* 0x001A2340 */
void glEnable(unsigned int cap);                                                    /* 0x001A2DB8 */
void glDisable(unsigned int cap);                                                   /* 0x001A2FB8 */
void glMatrixMode(unsigned int mode);                                               /* 0x001A3638 */
void glLoadMatrixf(const f32 *m);                                                   /* 0x001A3648 */
void glLoadIdentity(void);                                                          /* 0x001A3708 */
void glPushMatrix(void);                                                            /* 0x001A3738 */
void glPopMatrix(void);                                                             /* 0x001A3808 */
void glRotatef(f32 angle, f32 x, f32 y, f32 z);                                     /* 0x001A3858 */
void glScalef(f32 x, f32 y, f32 z);                                                 /* 0x001A3950 */
void glTranslatef(f32 x, f32 y, f32 z);                                             /* 0x001A3A00 */
void glMultMatrixf(const f32 *m);                                                   /* 0x001A3AB0 */
void glScissor(int x, int y, int width, int height);                                /* 0x001A3B18 */
void glViewport(int x, int y, int width, int height);                               /* 0x001A3B60 */
void glOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);        /* 0x001A3BA8 */
void glFrustum(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);      /* 0x001A3CA0 */
void gluPerspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar);                     /* 0x001A3DA0 */
void glBegin(unsigned int mode);                                                    /* 0x001A3ED8 */
void glVertex3f(f32 x, f32 y, f32 z);                                               /* 0x001A3F10 */
void glVertex3fv(const f32 *v);                                                     /* 0x001A3F88 */
void glTexCoord2f(f32 s, f32 t);                                                    /* 0x001A4010 */
void glTexCoord3f(f32 s, f32 t, f32 r);                                             /* 0x001A4048 */
void glTexCoord2fv(const f32 *v);                                                   /* 0x001A4078 */
void glColor3f(f32 r, f32 g, f32 b);                                                /* 0x001A40F0 */
void glColor4f(f32 r, f32 g, f32 b, f32 a);                                         /* 0x001A4138 */
void glColor3fv(const f32 *v);                                                      /* 0x001A4180 */
void glColor4fv(const f32 *v);                                                      /* 0x001A41D0 */
void glColor3i(int r, int g, int b);                                                /* 0x001A4228 */
void glColor4i(int r, int g, int b, int a);                                         /* 0x001A4248 */
void glColor4ub(u8 r, u8 g, u8 b, u8 a);                                            /* 0x001A4268 */
void glColor4ubv(const u8 *v);                                                      /* 0x001A4298 */
void glColor4iv(const int *v);                                                      /* 0x001A42C8 */
void glClearColor(f32 r, f32 g, f32 b, f32 a);                                      /* 0x001A4370 */
void glTexCoordPointer(int size, unsigned int type, int stride, const void *ptr);   /* 0x001A43C8 */
void glVertexPointer(int size, unsigned int type, int stride, const void *ptr);     /* 0x001A43E0 */
void glColorPointer(int size, unsigned int type, int stride, const void *ptr);      /* 0x001A43F8 */
void glEnableClientState(unsigned int array);                                       /* 0x001A4410 */
void glDisableClientState(unsigned int array);                                      /* 0x001A4490 */
void glLightModelfv(unsigned int pname, const f32 *params);                         /* 0x001A46F0 */
void glGetIntegerv(unsigned int pname, int *params);                                /* 0x001A47D8 */
void glBlendFunc(unsigned int sfactor, unsigned int dfactor);                       /* 0x001A4A60 */
}

#endif /* WHIRL_TOUR_GAME_GL_H */
