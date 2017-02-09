#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../glegle.h"



#define X .525731112119133606
#define Z .850650808352039932

//position de la camera
float ex=-7;
float ey=9;
float ez=4;

//pas de déplacement de la caméra utilisé dans fct keyboard
float pas_camera=1;

//position de la sphere
float sphereTranslateX = 0;
float sphereTranslateY = 0;
float sphereTranslateZ = 0;

GLfloat sommets[12][3] =
{
  {-X, 0, Z},
  {X, 0, Z},
  {-X, 0, -Z},
  {X, 0, -Z},
  {0, Z, X},
  {0, Z, -X},
  {0, -Z, X},
  {0, -Z, -X},
  {Z, X, 0},
  {-Z, X, 0},
  {Z, -X, 0},
  {-Z, -X, 0}
};

int sindex[20][3] =
{
  {0, 4, 1},
  {0, 9, 4},
  {9, 5, 4},
  {4, 5, 8},
  {4, 8, 1},
  {8, 10, 1},
  {8, 3, 10},
  {5, 3, 8},
  {5, 2, 3},
  {2, 7, 3},
  {7, 10, 3},
  {7, 6, 10},
  {7, 11, 6},
  {11, 0, 6},
  {0, 1, 6},
  {6, 1, 10},
  {9, 0, 11},
  {9, 11, 2},
  {9, 2, 5},
  {7, 2, 11},
};

void init(void)
{
   glClearColor (0.0, 1.0, 1.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
     //déplacement caméra
      case 'q':
         ex=ex-0.5;
         break;
      case 'f':
         ex=ex+0.5;
         break;
      case 's':
         ey=ey-0.5;
         break;
      case 'z':
         ey=ey+0.5;
         break;
      case 'd':
         ez=ez-0.5;
         break;
      case 'e':
         ez=ez+0.5;
         break;
      case 27:
         exit(0);
         break;
   }
   printf("%f, %f, %f\n", ex,ey,ez);
   glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
  switch(key)
    {
    case GLUT_KEY_UP:
      if(sphereTranslateX < 6) sphereTranslateX=sphereTranslateX+2;
    break;
    case GLUT_KEY_DOWN:
      if(sphereTranslateX > 0) sphereTranslateX=sphereTranslateX-2;
    break;
    case GLUT_KEY_LEFT:
      if(sphereTranslateZ > 0) sphereTranslateZ = sphereTranslateZ-2;
    break;
    case GLUT_KEY_RIGHT:
      if(sphereTranslateZ < 6) sphereTranslateZ=sphereTranslateZ+2;
    break;
  }
}

void display(void)
{
  int i;
  float col = 0;

  glLoadIdentity ();
  gluLookAt (ex, ey, ez, 4.0, 4.0, 4.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  //glRotatef(xRotation, 1, 0, 0);

  glScalef(1,1,1);

  cubev2(0,0,0, 8,1,8, 1,0,0);

  glTranslatef(sphereTranslateX+1, sphereTranslateY+1 ,sphereTranslateZ+1);
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  //glTranslatef(1,1,0);
  for(i = 0; i < 20; i++){
    triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], 2,2,2, col,col,col,2);
    col = col + 0.05;
  }

  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void my_timer(int v)
{
  // xRotation += .75;
   /*if(xRotation > 100)
    xRotation = 0;*/
   glutTimerFunc(20, my_timer, 1);
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   //activation de la profondeur, permet de ne pas afficher les polygones cach� par d'autres
   glEnable(GL_DEPTH_TEST);

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialInput);
   glutTimerFunc(20, my_timer, 1);

   glutMainLoop();
   return 0;
}
