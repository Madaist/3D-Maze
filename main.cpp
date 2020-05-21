#include <gl/freeglut.h>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "SOIL.h"
#include "cube.h"
#include "utils.h"
#include "drawings.h"
using namespace std;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,ly=-1.0f;
// XY position of the camera
float x=14.5f, y = 30.0f;
double pi = 3.1415;

int h_pressed = 0;
bool coliziune = false;
GLfloat floorshadow[4][4];
//GLfloat lightpos[] = {-12, -20, 6, 1};
GLfloat lightpos[] = {15, 15, 4, 1};
int levelRenderMode = NIVEL1;
int textureRenderMode = GRASS;
int shadowRenderMode = SHADOW;
int previousLevel = NIVEL1;

static float solidZ = MAXZ;
static float transparentZ = MINZ;
GLuint sphereList, cubeList;

GLuint leavesTexture, woodTexture;

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

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(previousLevel != levelRenderMode)
    {
        x=14.5f;
        y=30.0f;
        angle=0.0;
        lx=0.0f;
        ly=-1.0f;
        previousLevel = levelRenderMode;
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

    if(y <= -22)
        drawYouWinBanner();

    GLfloat poz[4] = {-12, -20, 3, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, poz);

    GLfloat amb[4] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_EMISSION, amb);
    GLfloat dif[4] = {2, 2, 2, 2};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    GLfloat spec[4] = {2,0, 0, 1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);

    //GLfloat poz1[4] = {-12, -14, 3, 1};
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

    ///umbra playerului
    if(shadowRenderMode == SHADOW)
    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glColor3f(0.f, 0.f, 0.f);
        glPushMatrix();

        glTranslatef(x, y, 0); // Translation to the camera center
        glRotatef(angle * 180/pi, 0,0, 1); // Rotate to correspond to the camera
        glScaled(0.5, 1, 1);
        glTranslatef(-0.5, -1.5, 0); // Offset to draw the object

        glMultMatrixf((GLfloat *) floorshadow);
        glutSolidCube(0.1);
        if(levelRenderMode != NIVEL1)
            drawHuman();
        glPopMatrix();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }

    ///playerul
    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(x, y, 0); // Translation to the camera center
    glRotatef(angle * 180/pi, 0,0, 1); // Rotate to correspond to the camera
    glTranslatef(0.01, -1, 0.25); // Offset to draw the object

    Cube player(0.1, Point(0, 0, 0.0));
    ///aici trebuie setat centrul cubului jucator (deoarece el are aplicate doua translatii si o rotatie
    /// => centrul cubului depinde si de transformari => il iau din rezultatul inmultirii matricelor
    player.centre = Point(0.001*cos(angle) + 1*sin(angle) + x,
                          0.001*sin(angle) - 1*cos(angle) + y,
                          0.25);

    if(levelRenderMode != NIVEL1)
        drawHuman();
    glPopMatrix();


    drawBeginningText();

    if(y > 20)
    {
      drawTrees();
    }

    vector<Cube> cuburi = drawMaze();

    if(checkAllCollisions(player, cuburi))
        coliziune = true;
    else
        coliziune = false;

    cuburi.clear();
    drawMazeCorners();
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

void init()
{
    woodTexture = LoadTexture("wood.png");
    leavesTexture = LoadTexture("leaves.png");
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

    init();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    solidZ = MAXZ;
    transparentZ = MINZ;
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

    glutCreateMenu(shadowMenu);
    glutAddMenuEntry("SHADOW", SHADOW);
    glutAddMenuEntry("NO SHADOW", NOSHADOW);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    v0[X] = -1000.f;
    v0[Y] = -1000.f;
    v0[Z] = 0;
    v1[X] = 1000.f;
    v1[Y] = 1000.f;
    v1[Z] = 0;
    v2[X] = -1000.f;
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
