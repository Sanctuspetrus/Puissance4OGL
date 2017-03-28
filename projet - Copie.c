
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funct.h"
#include "game.h"



#define X .525731112119133606
#define Z .850650808352039932

//position de la camera
float ex=0;
float ey=10;
float ez=-5;

//pas de déplacement de la caméra utilisé dans fct keyboard
float pas_camera=1;

//position de la sphere
float sphereTranslateX = 0;
float sphereTranslateY = 0;
float sphereTranslateZ = 0;

// Proprietes de la source lumineuse
//
GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1 };
GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1 };
GLfloat light_specular[] = { .9, .9,.9, 0 };
GLfloat light_position[] = { 2.0, 10.0, 2.0, 1.0 };

// Proprietes generales de l'eclairage
//
GLfloat general_light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

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
   glClearColor (0.0, 0.5, 1.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
     //déplacement caméra
      case 'q':
         ex=ex-0.5;
         break;
      case 'd':
         ex=ex+0.5;
         break;
      case 's':
         ey=ey-0.5;
         break;
      case 'z':
         ey=ey+0.5;
         break;
      case 'f':
         ez=ez-0.5;
         break;
      case 'r':
         ez=ez+0.5;
         break;
      case ' ':

        //on pose la boule
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
    case GLUT_KEY_LEFT:
      if(sphereTranslateX < 6) sphereTranslateX=sphereTranslateX+2;
    break;
    case GLUT_KEY_RIGHT:
      if(sphereTranslateX > 0) sphereTranslateX=sphereTranslateX-2;
    break;
    case GLUT_KEY_DOWN:
      if(sphereTranslateZ > 0) sphereTranslateZ = sphereTranslateZ-2;
    break;
    case GLUT_KEY_UP:
      if(sphereTranslateZ < 6) sphereTranslateZ=sphereTranslateZ+2;
    break;
  }
}

void display(void)
{
  int i;

  glLoadIdentity ();
  gluLookAt (ex, ey, ez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, general_light_ambient);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);

  //glPushMatrix();
  //glRotatef(xRotation, 1, 0, 0);

  glScalef(1,1,1);

  cubev2(-4,0,0, 8,1,8, 0.0,0.0,1.0);

  glTranslatef(sphereTranslateX-3, sphereTranslateY+2 ,sphereTranslateZ+1);
  //GL_LINE pour fils de fer, GL_FILL pour remplissage
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  for(i = 0; i < 20; i++){
    triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], 2,2,2, 0.0,1.0,0.0,2);
  }

//  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(90,w/h,1,50);
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


/* pour l'afficahge de texte
* dans le display :
* glDisable(GL_NOLMALIZE);
* glDisable(GL_LIGHTING);
*/

/* pour le texte :
* DABORD => glColor3f
* PUIS => glWindowPos2i(x,y);
* ENFIN => glutBitmapString(GLUT_BITMAP_HELVETICA_12, leTexteIci en char*);
*/
