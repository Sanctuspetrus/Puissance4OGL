#include <GL/glut.h>


void cube(int x,int y,int z,int scalex, int scaley, int scalez,float col1,float col2,float col3);

void triangle(float *p1,float *p2,float *p3,int scalex, int scaley, int scalez,float col1,float col2,float col3);
void calcul_normal(float v[3])
;
void triangle_rec(float *p1,float *p2,float *p3,int scalex, int scaley, int scalez,float col1,float col2,float col3, int rec);
