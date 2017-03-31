#include <GL/glut.h>

#define FRONT 0
#define LEFT 1
#define BACK 2
#define RIGHT 3

void cube(int x,int y,int z,int scalex, int scaley, int scalez,float col1,float col2,float col3);

void cubev2(int x,int y,int z,int scalex, int scaley, int scalez,float col1,float col2,float col3);

void triangle(float *p1,float *p2,float *p3,float scalex, float scaley, float scalez,float col1,float col2,float col3);

void calcul_normal(float v[3]);

void triangle_rec(float *p1,float *p2,float *p3,float scalex, float scaley, float scalez,float col1,float col2,float col3, int rec);
