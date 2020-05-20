#include <gl/freeglut.h>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "SOIL.h"
#include "cube.h"
#include "declarations.h"
#include "utils.h"
using namespace std;


// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,ly=-1.0f;
// XY position of the camera
float x=14.5f, y=30.0f;
double pi = 3.1415;

int h_pressed = 0;
bool coliziune = false;
GLfloat floorshadow[4][4];
//GLfloat lightpos[] = {-12, -20, 6, 1};
GLfloat lightpos[] = {15, 15, 4, 1};
int levelRenderMode = NIVEL1;

enum
{
    GRASS, WATER, MARBLE, STONE
};
int textureRenderMode = GRASS;

enum
{
    X, Y, Z, W
};
enum
{
    A, B, C, D
};

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4

static float solidZ = MAXZ;
static float transparentZ = MINZ;
static GLuint sphereList, cubeList;

void animate(void)
{
    if (solidZ <= MINZ || transparentZ >= MAXZ)
        glutIdleFunc(NULL);
    else
    {
        solidZ -= ZINC;
        transparentZ += ZINC;
        glutPostRedisplay();
    }
}


void levelMenu(int selection)
{
    levelRenderMode = selection;
    glutPostRedisplay();
}

void textureMenu(int selection)
{
    textureRenderMode = selection;
    glutPostRedisplay();
}


void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

}

void drawGround()
{
    glEnable(GL_TEXTURE_2D);

    if(levelRenderMode == NIVEL1)
        LoadTexture ("grasss.png" );
    else if(levelRenderMode == NIVEL2)
        LoadTexture("pietre.png");
    else if(levelRenderMode == NIVEL3)
        LoadTexture("water2.png");

    if(textureRenderMode == GRASS)
        LoadTexture ("grasss.png" );
    else  if(textureRenderMode == STONE)
        LoadTexture ("pietre.png" );
    else   if(textureRenderMode == WATER)
        LoadTexture ("water2.png" );
    else if(textureRenderMode == MARBLE)
        LoadTexture ("marble.png" );

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(1000.0, 1000.0);
    glVertex3f(-1000.0f, -1000, 0.0f);
    glTexCoord2f(1000.0, 0.0);
    glVertex3f(-1000.0f, 1000.0f,  0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f( 1000.0f, 1000.0f,  0.0f);
    glTexCoord2f(0.0, 1000.0);
    glVertex3f( 1000.0f, -1000.0f, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


/* create a matrix that will project the desired shadow */
void
shadowmatrix(GLfloat shadowMat[4][4],
             GLfloat groundplane[4],
             GLfloat lightpos[4])
{
    GLfloat dot;

    /* find dot product between light position vector and ground plane normal */
    dot = groundplane[X] * lightpos[X] +
          groundplane[Y] * lightpos[Y] +
          groundplane[Z] * lightpos[Z] +
          groundplane[W] * lightpos[W];

    shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
    shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
    shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
    shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

    shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
    shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
    shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
    shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

    shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
    shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
    shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
    shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

    shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
    shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
    shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
    shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}

/* find the plane equation given 3 points */
void
findplane(GLfloat plane[4],
          GLfloat v0[3], GLfloat v1[3], GLfloat v2[3])
{
    GLfloat vec0[3], vec1[3];

    /* need 2 vectors to find cross product */
    vec0[X] = v1[X] - v0[X];
    vec0[Y] = v1[Y] - v0[Y];
    vec0[Z] = v1[Z] - v0[Z];

    vec1[X] = v2[X] - v0[X];
    vec1[Y] = v2[Y] - v0[Y];
    vec1[Z] = v2[Z] - v0[Z];

    /* find cross product to get A, B, and C of plane equation */
    plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
    plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
    plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];

    plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);
}


void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(y <= -27)
    {
        glColor3f(0, 0, 0);
        glRasterPos3d(-15, -29, 0.5);
        const char congrats[] = "Congratulations! You won.";
        int len = strlen(congrats);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, congrats[i]);
    }

    glClearColor (0, 0, 1, 1.0);
    glLoadIdentity();

    if((h_pressed % 2) == 0)
        gluLookAt(	x, y, 0.2, x+lx, y+ly,  0.2, 0.0f, 0.0f,  1.0f);
    else
    {
        glDisable(GL_FOG);
        glRotated(180, 0, 0, 1);
        gluLookAt(0, 5, 70,    0, 0, 1,    0.0f, 1.0f, 0.0f);
    }


    GLfloat poz[4] = {-12, -20, 3, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    GLfloat amb[4] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_EMISSION, amb);
    GLfloat dif[4] = {2, 2, 2, 2};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    GLfloat spec[4] = {2,0, 0, 1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);

    GLfloat poz1[4] = {-12, -14, 3, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_EMISSION, amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);


    if(levelRenderMode != NIVEL2)
    {
        GLfloat modelamb[4] = {0.4, 0.4, 0.4, 1};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelamb);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        GLfloat em[4] = {0,0,0,1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
    }
    else
    {
        GLfloat em[4] = {0, 0, 1,1};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
        glEnable(GL_COLOR_MATERIAL);
    }

    if(levelRenderMode == NIVEL3)
    {
        glEnable(GL_FOG);

        GLfloat fogColor[4] = {0.8, 0.5, 0.5, 1.0};
        glFogi (GL_FOG_MODE, GL_LINEAR);
        glFogfv (GL_FOG_COLOR, fogColor);
        glFogf (GL_FOG_DENSITY, 0.2);
        glHint (GL_FOG_HINT, GL_FASTEST);
        glFogf (GL_FOG_START, 1.0);
        glFogf (GL_FOG_END, 7.0);
    }
    else
        glDisable(GL_FOG);

    drawGround();


    ///player
    glColor3f(1, 0, 1);

    glPushMatrix();
    glTranslatef(x, y, 0); // Translation to the camera center
    glRotatef(angle * 180/pi, 0,0, 1); // Rotate to correspond to the camera
    glTranslatef(0.01, -1, 0.25); // Offset to draw the object

    Cube player(0.1, Point(0, 0, 0.0));
    ///aici trebuie setat centrul cubului jucator (deoarece el are aplicate doua translatii si o rotatie
    /// => centrul cubului depinde si de transformari => il iau din rezultatul inmultirii matricelor
    player.centre = Point(0.01*cos(angle) + 1*sin(angle) + x,
                          0.01*sin(angle) - 1*cos(angle) + y,
                          0.25);

    if(levelRenderMode != NIVEL1)
        drawHuman();

    glPopMatrix();


    glColor3f(0, 0, 0);
    if(levelRenderMode != NIVEL2)
        glRasterPos3d(15.3, 20,  3);
    else
        glRasterPos3d(18, 20,  0.8);
    const char goodluck[] = "Good luck!";
    int len = strlen(goodluck);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, goodluck[i]);


    if(levelRenderMode == NIVEL3)
    {
        glRasterPos3d(17, 20,  2.5);
        const char fognotification[] = "Everything is foggy here. Will you find the exit?";
        len = strlen(fognotification);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fognotification[i]);
    }

    if(levelRenderMode == NIVEL2)
    {
        glRasterPos3d(18.6, 20,  0.5);
        const char bluenotification[] = "Are the blue areas you see a";
        len = strlen(bluenotification);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, bluenotification[i]);
    }

    if(levelRenderMode == NIVEL2)
    {
        glRasterPos3d(18.8, 20,  0.2);
        const char bluenotification[] = " cube or the exit? Can you tell?";
        len = strlen(bluenotification);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, bluenotification[i]);
    }
    /*
        ///obiectul caruia vreau sa i pun umbra
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glColor3f(0.f, 0.f, 0.f);

        glPushMatrix();
        glTranslated(17, 10, 0.6);
        glMultMatrixf((GLfloat *) floorshadow);

        glutSolidCube(0.5);
        glPopMatrix();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);

        glColor3f(0.4, 1, 0.2);
        glPushMatrix();
        glTranslated(17, 11, 0.6);
        glutSolidCube(0.5);
        glPopMatrix();
    */

    vector<Cube> cuburi = drawMaze();

    if(checkAllCollisions(player, cuburi))
        coliziune = true;
    else
        coliziune = false;

    cuburi.clear();

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
    GLfloat mat_shininess[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    sphereList = glGenLists(1);
    glNewList(sphereList, GL_COMPILE);
    glutSolidSphere (0.8, 16, 16);
    glEndList();
    cubeList = glGenLists(1);
    glNewList(cubeList, GL_COMPILE);
    glutSolidCube (1.5);
    glEndList();


    GLfloat mat_solid[] = { 0.75, 0.75, 0.0, 1.0 };
    GLfloat mat_zero[] = { 1.0, 0.0, 0.0, 1.0 };//
    GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
    GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };//

//cub sfera colt stanga jos
    glPushMatrix ();
    glTranslatef (20, 15, 2.6);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();


    glPushMatrix ();
    glTranslatef (20, 15, 1.7);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    glCallList (cubeList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();


    //cub sfera colt dreapta jos
    glPushMatrix ();
    glTranslatef (-23, 14.8, 2.6);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();


    glPushMatrix ();
    glTranslatef (-23, 14.8, 1.7);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    glCallList (cubeList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();

    //cub sfera colt stanga sus

    glPushMatrix ();
    glTranslatef (19.9, -28.2, 2.6);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();


    glPushMatrix ();
    glTranslatef (19.9, -28.2, 1.7);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    glCallList (cubeList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();

    //cub sfera colt dreapta sus

    glPushMatrix ();
    glTranslatef (-23, -28, 2.6);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();


    glPushMatrix ();
    glTranslatef (-23, -28, 1.7);

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    glCallList (cubeList);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glPopMatrix ();
    glPopMatrix ();


    glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy)
{
    float fraction = 0.2f;
    if(key == 'd' || key == 'D')
    {
        angle -= 0.03f;
        lx = sin(angle);
        ly = -cos(angle);
    }
    else if(key == 'a' || key == 'A')
    {
        angle += 0.03f;
        lx = sin(angle);
        ly = -cos(angle);
    }
    else if(key == 'w' || key == 'W')
    {
        if(coliziune == false)
        {
            x += lx * fraction;
            y += ly * fraction;
        }
    }
    else if(key == 's' || key == 'S')
    {
        x -= lx * fraction;
        y -= ly * fraction;
    }
    else if(key == 'h' || key == 'H')
    {
        h_pressed += 1;
    }
}


int main(int argc, char **argv)
{
    GLfloat plane[4];
    GLfloat v0[3], v1[3], v2[3];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000,700);
    glutCreateWindow("Maze");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    solidZ = MAXZ;
    transparentZ = MINZ;
    // glutIdleFunc(animate);
    glutKeyboardFunc(processKeys);

    glEnable(GL_DEPTH_TEST);

    glutCreateMenu(levelMenu);
    glutAddMenuEntry("LEVEL 1 ", NIVEL1);
    glutAddMenuEntry("LEVEL 2", NIVEL2);
    glutAddMenuEntry("LEVEL 3", NIVEL3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutCreateMenu(textureMenu);
    glutAddMenuEntry("GRASS TEXTURE", GRASS);
    glutAddMenuEntry("STONE TEXTURE", STONE);
    glutAddMenuEntry("WATER TEXTURE", WATER);
    glutAddMenuEntry("MARBLE TEXTURE", MARBLE);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    v0[X] = -100.f;
    v0[Y] = -1000.f;
    v0[Z] = 0;
    v1[X] = -1000.f;
    v1[Y] = 1000.f;
    v1[Z] = 0;
    v2[X] = 1000.f;
    v2[Y] = 1000.f;
    v2[Z] = 0;

    findplane(plane, v0, v1, v2);
    shadowmatrix(floorshadow, plane, lightpos);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);

    glutMainLoop();

    return 1;
}
