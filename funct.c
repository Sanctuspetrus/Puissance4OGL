#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./funct.h"


void cube(int x,int y,int z,int scalex, int scaley, int scalez,float col1,float col2,float col3){
   glScalef(scalex,scaley,scalez);

   glColor3f (col1, col2, col3);
   glBegin(GL_POLYGON);
      glVertex3f (x,   y,   z  );
      glVertex3f (x+1, y,   z  );
      glVertex3f (x+1, y+1, z  );
      glVertex3f (x,   y+1, z  );
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f (x,   y,   z  );
      glVertex3f (x+1, y,   z  );
      glVertex3f (x+1, y,   z+1);
      glVertex3f (x,   y,   z+1);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f (x,   y,   z+1);
      glVertex3f (x+1, y,   z+1);
      glVertex3f (x+1, y+1, z+1);
      glVertex3f (x,   y+1, z+1);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f (x+1, y,   z  );
      glVertex3f (x+1, y+1, z  );
      glVertex3f (x+1, y+1, z+1);
      glVertex3f (x+1, y,   z+1);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f (x  , y+1, z  );
      glVertex3f (x+1, y+1, z  );
      glVertex3f (x+1, y+1, z+1);
      glVertex3f (x  , y+1, z+1);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f (x  , y,   z  );
      glVertex3f (x  , y+1, z  );
      glVertex3f (x  , y+1, z+1);
      glVertex3f (x  , y  , z+1);
   glEnd();
 }


 void cubev2(int x,int y,int z,int scalex, int scaley, int scalez,float col1,float col2,float col3){


    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glColor3f (col1, col2, col3);
    glBegin(GL_POLYGON);
       glVertex3f (x,   y,   z  );
       glVertex3f (x+scalex, y,   z  );
       glVertex3f (x+scalex, y+scaley, z  );
       glVertex3f (x,   y+scaley, z  );
    glEnd();

    glBegin(GL_POLYGON);
       glVertex3f (x,   y,   z  );
       glVertex3f (x+scalex, y,   z  );
       glVertex3f (x+scalex, y,   z+scalez);
       glVertex3f (x,   y,   z+scalez);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex3f (x,   y,   z+scalez);
       glVertex3f (x+scalex, y,   z+scalez);
       glVertex3f (x+scalex, y+scaley, z+scalez);
       glVertex3f (x,   y+scaley, z+scalez);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex3f (x+scalex, y,   z  );
       glVertex3f (x+scalex, y+scaley, z  );
       glVertex3f (x+scalex, y+scaley, z+scalez);
       glVertex3f (x+scalex, y,   z+scalez);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex3f (x  , y+scaley, z  );
       glVertex3f (x+scalex, y+scaley, z  );
       glVertex3f (x+scalex, y+scaley, z+scalez);
       glVertex3f (x  , y+scaley, z+scalez);
    glEnd();

    glBegin(GL_POLYGON);
       glVertex3f (x  , y,   z  );
       glVertex3f (x  , y+scaley, z  );
       glVertex3f (x  , y+scaley, z+scalez);
       glVertex3f (x  , y  , z+scalez);
    glEnd();
  }



void triangle(float *p1,float *p2,float *p3,int scalex, int scaley, int scalez,float col1,float col2,float col3){

   glColor3f (col1, col2, col3);
   glBegin(GL_POLYGON);
      glVertex3f (p1[0], p1[1], p1[2]);
      glVertex3f (p2[0], p2[1], p2[2]);
      glVertex3f (p3[0], p3[1], p3[2]);
   glEnd();

}

void calcul_normal(float v[3])
{
        float d=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
        v[0]=v[0]/d;
        v[1]=v[1]/d;
        v[2]=v[2]/d;
}

void triangle_rec(float *p1,float *p2,float *p3,int scalex, int scaley, int scalez,float col1,float col2,float col3, int rec){

	float p4[3];
	float p5[3];
	float p6[3];


	if(rec > 0){


	p4[0] = (p1[0]+p2[0])/2;
	p4[1] = (p1[1]+p2[1])/2;
	p4[2] = (p1[2]+p2[2])/2;

	p5[0] = (p1[0]+p3[0])/2;
	p5[1] = (p1[1]+p3[1])/2;
	p5[2] = (p1[2]+p3[2])/2;

	p6[0] = (p2[0]+p3[0])/2;
	p6[1] = (p2[1]+p3[1])/2;
	p6[2] = (p2[2]+p3[2])/2;

	calcul_normal(p4);
	calcul_normal(p5);
	calcul_normal(p6);

	triangle_rec(p1,p4,p5,scalex,scaley,scalez,col1,col2,col3, rec-1);
	triangle_rec(p4,p2,p6,scalex,scaley,scalez,col1+0.02,col2+0.02,col3+0.02,rec-1);
	triangle_rec(p4,p5,p6,scalex,scaley,scalez,col1+0.04,col2+0.04,col3+0.04,rec-1);
	triangle_rec(p5,p6,p3,scalex,scaley,scalez,col1+0.06,col2+0.06,col3+0.06,rec-1);

	}else{
		triangle(p1,p2,p3,scalex, scaley, scalez,col1,col2,col3);
	}


}
