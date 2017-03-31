
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funct.h"
#include "game.h"



#define X .525731112119133606
#define Z .850650808352039932

#define VITESSEDEPLACEMENT 1

#define TAILLEECRAN 500

#define TAILLEBOULE 0.75

Game* game;
Cursor* cursor;

int victory = 0;

//position de la camera
float ex=0;
float ey=0;
float ez=0;

//pas de déplacement de la caméra utilisé dans fct keyboard
float pas_camera=1;

//texte affiché à l'écran
char* textGame = "";

//position de la sphere
float sphereTranslateX = 0;
float sphereTranslateY = 0;
float sphereTranslateZ = 0;

//variables utilisées pour le déplacement de la scène
short enDeplacement = 0;
short positionScene = 0;
short nbDeplacement = 0;
short direction = 0;

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

void nextPositionScene(short next){
  positionScene += next;
  if(positionScene < 0) {
    positionScene = 3;
  }
  if(positionScene > 3){
    positionScene = 0;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  if(enDeplacement == 0){
   switch (key) {
     //déplacement caméra
      case 'q':
         ey=ey-3;
         enDeplacement = 1;
         direction = -1;
         nextPositionScene(-1);
         break;
      case 'd':
         ey=ey+3;
         enDeplacement = 1;
         direction = 1;
         nextPositionScene(1);
         break;
      case 's':
         ex=ex+3;
         break;
      case 'z':
         ex=ex-3;
         break;
      case 'f':
         ez=ez-3;
         break;
      case 'r':
         ez=ez+3;
         break;
      case 'p':
        victory = 0;
        textGame = "";
        resetGame(game);
        break;
      case ' ' :
        if(victory == 0){
          //on pose la boule
          putBallDown(game);
        // /  printGame(*game);
        }
        break;
      case 27:
         exit(0);
         break;
   }
 }
 glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
  if(victory == 0){
    switch(key)
      {
        case GLUT_KEY_LEFT:
        if(positionScene == FRONT){
            cursorLeft(cursor);
        }else if (positionScene == LEFT){
            cursorBack(cursor);
        }else if (positionScene == BACK){
            cursorRight(cursor);
        }else if (positionScene == RIGHT){
            cursorFront(cursor);
        }
        break;
        case GLUT_KEY_RIGHT:
        if(positionScene == FRONT){
            cursorRight(cursor);
        }else if (positionScene == LEFT){
            cursorFront(cursor);
        }else if (positionScene == BACK){
            cursorLeft(cursor);
        }else if (positionScene == RIGHT){
            cursorBack(cursor);
        }
        break;
        case GLUT_KEY_DOWN:
        if(positionScene == FRONT){
            cursorFront(cursor);
        }else if (positionScene == LEFT){
            cursorLeft(cursor);
        }else if (positionScene == BACK){
            cursorBack(cursor);
        }else if (positionScene == RIGHT){
            cursorRight(cursor);
        }
        break;
        case GLUT_KEY_UP:
        if(positionScene == FRONT){
            cursorBack(cursor);
        }else if (positionScene == LEFT){
            cursorRight(cursor);
        }else if (positionScene == BACK){
            cursorFront(cursor);
        }else if (positionScene == RIGHT){
            cursorLeft(cursor);
        }
        break;
    }
  }
}

void display(void)
{
  int i;
  int z;
  int y;
  int x;

  glLoadIdentity ();
  gluLookAt (0, 13, -3, 0.0, -5.0, 0.0, 0.0, 0.5, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
  glWindowPos2i(TAILLEECRAN/2-100, 15);
  glutBitmapString(GLUT_BITMAP_HELVETICA_12, textGame);

  glPopMatrix();

  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, general_light_ambient);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);

  glRotatef(ex,1,0,0);
  glRotatef(ey,0,1,0);
  glRotatef(ez,0,0,1);

  glScalef(1,1,1);



  glPushMatrix();
  cubev2(-4,0,-4, 8,1,8, 0.0,0.0,1.0);

  //affichage de toutes les boules posées
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  for (z = 0; z < GAME_SIZE; z++) {
		for (y = 0; y < GAME_SIZE; y++) {
			for (x = 0; x < GAME_SIZE; x++) {
        //BOULE BLANCHE
        if(getPosColorAt(*game, x, y, z) == WHITE) {
          glPushMatrix();
          glTranslatef((GAME_SIZE-x-2.5)*2,(GAME_SIZE-y)*1.5,(GAME_SIZE-z-2.5)*2);
		  	glPushMatrix();
		  	glScalef(TAILLEBOULE, TAILLEBOULE, TAILLEBOULE);
          for(i = 0; i < 20; i++){
            triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], TAILLEBOULE,TAILLEBOULE,TAILLEBOULE, 1.0,1.0,1.0,2);
          }
          glPopMatrix();
          glPopMatrix();
	  }
        //BOULE NOIRE
        if(getPosColorAt(*game, x, y, z) == BLACK) {
          glPushMatrix();
          glTranslatef((GAME_SIZE-x-2.5)*2,(GAME_SIZE-y)*1.5,(GAME_SIZE-z-2.5)*2);
		  	glPushMatrix();
		  	glScalef(TAILLEBOULE, TAILLEBOULE, TAILLEBOULE);
          for(i = 0; i < 20; i++){
           triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], TAILLEBOULE,TAILLEBOULE,TAILLEBOULE, 0.0,0.0,0.0,2);
          }
          glPopMatrix();
          glPopMatrix();
        }
      }
    }
  }


  glPushMatrix();
  glTranslatef((cursor->x-1.5)*-2, (GAME_SIZE*1.5)-(cursor->y + fall(*game))*1.5 ,(cursor->z - 1.5)*-2);
	glPushMatrix();
	glScalef(TAILLEBOULE, TAILLEBOULE, TAILLEBOULE);

  //GL_LINE pour fils de fer, GL_FILL pour remplissage
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  if(getColor(*game) == 1){
    for(i = 0; i < 20; i++){
      triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], TAILLEBOULE,TAILLEBOULE,TAILLEBOULE, 1.0,1.0,1.0,2);
    }
  }else if(getColor(*game) == -1){
    for(i = 0; i < 20; i++){
      triangle_rec(sommets[sindex[i][0]], sommets[sindex[i][1]], sommets[sindex[i][2]], TAILLEBOULE,TAILLEBOULE,TAILLEBOULE, 0.0,0.0,0.0,2);
    }
  }
  glPopMatrix();//Scale
  glPopMatrix();//Translation

  glPopMatrix();
  glutSwapBuffers();
  if(validateGame(game) == WIN_BLACK){
    textGame = "VICTOIRE DU JOUEUR NOIR";
    victory = 1;
  }
  if(validateGame(game) == WIN_WHITE){
    textGame = "VICTOIRE DU JOUEUR BLANC";
    victory = 1;
  }
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

  if(enDeplacement == 1){
    if(nbDeplacement < 87){
      ey += VITESSEDEPLACEMENT * direction;
      nbDeplacement++;
    }if(nbDeplacement == 87){
      enDeplacement = 0;
      nbDeplacement = 0;
    }
  }

   glutTimerFunc(5, my_timer, 1);
   glutPostRedisplay();
}

int main(int argc, char** argv)
{

   initGame(&game);
   cursor = game->cursor;

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutInitWindowSize (TAILLEECRAN, TAILLEECRAN);
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
