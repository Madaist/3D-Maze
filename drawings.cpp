#include <gl/freeglut.h>
#include "drawings.h"
#include "cube.h"
#include "SOIL.h"
#include "utils.h"
#include<iostream>


void drawGround()
{
    extern int levelRenderMode, textureRenderMode;
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


void drawHuman()
{
    GLUquadricObj *body;
    body = gluNewQuadric ( );
    gluQuadricDrawStyle (body,  GLU_FILL);
    glTranslatef( 0, 0, -0.1 );
    glPushMatrix();
    gluCylinder (body, 0.06, 0.06, 0.15, 10, 1);
    glPopMatrix();

    glColor3f(0,0,1);
    GLUquadricObj *foot1;
    foot1 = gluNewQuadric ( );
    gluQuadricDrawStyle (foot1,  GLU_FILL);
    glTranslatef( 0.03, 0,-0.3 );
    gluCylinder (foot1, 0.02, 0.02, 0.3, 10, 1);


    GLUquadricObj *foot2;
    foot2 = gluNewQuadric ( );
    gluQuadricDrawStyle (foot2,  GLU_FILL);
    glTranslatef( -0.06, 0, 0);
    gluCylinder (foot2, 0.02, 0.02, 0.3, 10, 1);

    glColor3f(1, 0.9, 0.9);
    GLUquadricObj *hand1;
    hand1 = gluNewQuadric ( );
    gluQuadricDrawStyle (hand1,  GLU_FILL);
    glTranslatef( -0.07, 0.02, 0.35);
    glRotated(30, 0, 1, 0);
    gluCylinder (hand1, 0.01, 0.01, 0.1, 10, 1);

    GLUquadricObj *hand2;
    hand2 = gluNewQuadric ( );
    gluQuadricDrawStyle (hand2,  GLU_FILL);
    glTranslatef( 0.17, 0, 0.105);
    glRotated(-65, 0, 1, 0);
    gluCylinder (hand2, 0.01, 0.01, 0.1, 10, 1);

    glTranslated(0, 0.01, 0.175);
    glutSolidSphere(0.05, 10, 10);

    glPopMatrix();
}

void drawTree()
{

    extern GLuint leavesTexture, woodTexture;

    ///bradut
    ///trunchi
    glColor3f(1, 1, 1);
    GLuint cylinderList = glGenLists(4);
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_FLAT);
    gluQuadricTexture(qobj, GL_TRUE);
    glNewList(cylinderList, GL_COMPILE);
    gluCylinder(qobj, 0.4, 0.3, 1, 15, 5);
    glEndList();

    glShadeModel (GL_FLAT);
    glPushMatrix();
    glTranslatef(21, 22, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glCallList(cylinderList);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///primul nivel
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_FLAT);
    gluQuadricTexture(qobj, GL_TRUE);
    glNewList(cylinderList + 1, GL_COMPILE);
    gluCylinder(qobj, 0.9, 0.2, 1, 15, 5);
    glEndList();

    glShadeModel (GL_FLAT);
    glPushMatrix();
    glTranslatef(21, 22, 0.6);

    glBindTexture(GL_TEXTURE_2D, leavesTexture);
    glEnable(GL_TEXTURE_2D);
    glCallList(cylinderList + 1);
    glPopMatrix();

    ///al doilea nivel
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_FLAT);
    gluQuadricTexture(qobj, GL_TRUE);
    glNewList(cylinderList + 2, GL_COMPILE);
    gluCylinder(qobj, 0.7, 0.1, 1, 15, 5);
    glEndList();

    glShadeModel (GL_FLAT);
    glPushMatrix();
    glTranslatef(21, 22, 1.2);
    glEnable(GL_TEXTURE_2D);
    glCallList(cylinderList + 2);
    glPopMatrix();

    ///al treilea nivel
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_FLAT);
    gluQuadricTexture(qobj, GL_TRUE);
    glNewList(cylinderList + 3, GL_COMPILE);
    gluCylinder(qobj, 0.5, 0, 1, 15, 5);
    glEndList();

    glShadeModel (GL_FLAT);
    glPushMatrix();
    glTranslatef(21, 22, 1.7);
    glEnable(GL_TEXTURE_2D);
    glCallList(cylinderList + 3);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void drawTrees()
{
    extern int levelRenderMode;

    glPushMatrix();
    glTranslated(-1.7, -1.5, 0);
    drawTree();
    glPopMatrix();
    if(levelRenderMode != NIVEL2)
    {
        glPushMatrix();
        glTranslated(-5, 0, 0);
        drawTree();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-8, 0, 0);
        drawTree();
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslated(-8, 0, 0);
        drawTree();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-10, 0, 0);
        drawTree();
        glPopMatrix();
    }
}

void drawMazeCorners()
{
    ///sferele si cuburile din colturi -> amestecare + obiecte quadrice
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
    GLfloat mat_shininess[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    sphereList = glGenLists(1);
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(sphereList, GL_COMPILE);
    gluSphere (qobj, 0.8, 16, 16);
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
    glTranslatef (19.9, -28, 2.6);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
    glCallList (sphereList);
    glPopMatrix ();


    glPushMatrix ();
    glTranslatef (19.9, -28, 1.7);
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
}

void drawBeginningText()
{
    extern int levelRenderMode;
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
}

void drawYouWinBanner()
{
    glEnable(GL_TEXTURE_2D);
    LoadTexture("youwin2.png");

    glColor3f(1, 1, 1.5);
    glPushMatrix();
    glTranslated(-31, -60, 1);
    glBegin(GL_POLYGON);
    glTexCoord2f(-0.2, 1.0);
    glVertex3d(15, 27, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(12, 27, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(12, 27, 0.2);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(15, 27, 0.2);
    glEnd();

    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    LoadTexture("trophy.png");
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1.0);
    glVertex3d(15.8, 27, 0.9);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(15.2, 27, 0.9);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(15.2, 27, 0.3);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(15.8, 27, 0.3);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    LoadTexture("trophy.png");
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1.0);
    glVertex3d(11.8, 27, 0.9);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(11.2, 27, 0.9);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(11.2, 27, 0.3);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(11.8, 27, 0.3);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    LoadTexture("trophy.png");
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1.0);
    glVertex3d(15.8, 27, 0.9);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(15.2, 27, 0.9);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(15.2, 27, 0.3);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(15.8, 27, 0.3);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

std::vector<Cube> drawMaze()
{
    extern int levelRenderMode;


    std::vector<Cube> cuburi;
    ///labirintul
    ///latura de jos
    float lat = 1.5;
    float cubeCentreZ = 0.6;

    glColor3f(1, 1, 0);
    for(int i = 0; i < 3; i++)
    {
        glPushMatrix();
        Cube cub(lat, Point(20-i*lat, 15, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    for(int i = 0; i < 25; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,0);
        else
            glColor3f(0,0,0);
        glPushMatrix();
        Cube cub(lat, Point(13-i*lat, 15, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///perete stanga

    for(int i = 0; i < 29; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 0, 0);
        else
            glColor3f(1, 1, 1);
        glPushMatrix();
        Cube cub(lat, Point(20, 15-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///perete dreapta
    for(int i = 0; i < 29; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 0, 0);
        else
            glColor3f(1, 1, 1);
        glPushMatrix();
        Cube cub(lat, Point(-23, 15-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///perete sus
    for(int i = 0; i < 23; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,0);
        else
            glColor3f(0,0,0);
        glPushMatrix();
        Cube cub(lat, Point(20-i*lat, -28, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,0);
        else
            glColor3f(0,0,0);
        glPushMatrix();
        Cube cub(lat, Point(-20-i*lat, -28, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 1
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        glPushMatrix();
        Cube cub(lat, Point(13, 13.5-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 2
    for(int i = 0; i < 4; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,1,0);
        else
            glColor3f(0.5,0,0.5);
        glPushMatrix();
        Cube cub(lat, Point(11.5-i*lat, 10.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 7
    for(int i = 0; i < 5; i++)
    {
        if(i % 2 == 0)
            glColor3f(0.5, 1, 0.5);
        else
            glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
        Cube cub(lat, Point(-11, 15-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 8
    if(levelRenderMode != NIVEL2)
    {
        for(int i = 0; i < 7; i++)
        {
            if(i % 2 == 0)
                glColor3f(1, 0.5, 0.5);
            else
                glColor3f(0.5, 0.5, 1);
            glPushMatrix();
            Cube cub(lat, Point(-6.5-i*lat, 7.5, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 5
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,1,1);
            else
                glColor3f(0.5,0,0.5);
            glPushMatrix();
            Cube cub(lat, Point(1-i*lat, 11, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 6
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 7; i++)
        {
            if(i % 2 == 0)
                glColor3f(0, 1, 1);
            else
                glColor3f(0, 0, 0);
            glPushMatrix();
            Cube cub(lat, Point(1, 9.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 3
    for(int i = 0; i < 7; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        glPushMatrix();
        Cube cub(lat, Point(16.5, 9-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 4
    if(levelRenderMode != NIVEL2)
    {
        for(int i = 0; i < 6; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,1,0);
            else
                glColor3f(0.5,0,0.5);
            glPushMatrix();
            Cube cub(lat, Point(15-i*lat, 4.5, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 15
    if(levelRenderMode != NIVEL2)
    {
        for(int i = 0; i < 5; i++)
        {
            if(i % 2 == 0)
                glColor3f(1, 0.5, 0.5);
            else
                glColor3f(0.5, 0.5, 1);
            glPushMatrix();
            Cube cub(lat, Point(4-i*lat, -1, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 14
    for(int i = 0; i < 5; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 1, 1);
        else
            glColor3f(0, 0, 0);
        glPushMatrix();
        Cube cub(lat, Point(4, -2.5-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 13
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(8.5-i*lat, -8.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 16
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 1, 1);
        else
            glColor3f(0, 0, 0);
        glPushMatrix();
        Cube cub(lat, Point(-2, -2.5-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 17
    for(int i = 0; i < 4; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(-3.5-i*lat, -5.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 18
    for(int i = 0; i < 9; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 1, 1);
        else
            glColor3f(0, 0, 0);
        glPushMatrix();
        Cube cub(lat, Point(-9.5, 2-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 19
    for(int i = 0; i < 2; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(-6.5-i*lat, 2, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 20
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 2; i++)
        {
            if(i % 2 == 0)
                glColor3f(1, 0.5, 0.5);
            else
                glColor3f(0.5, 0.5, 1);
            glPushMatrix();
            Cube cub(lat, Point(-11-i*lat, -2.5, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 21
    if(levelRenderMode == NIVEL3)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i % 2 == 0)
                glColor3f(0, 1, 1);
            else
                glColor3f(0, 0, 0);
            glPushMatrix();
            Cube cub(lat, Point(-14, 0.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 12
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(-18.5-i*lat, 3, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 11
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(18.5-i*lat, -13.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 10
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(15.5, -7.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 9
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 2; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,1,0);
            else
                glColor3f(0.5,0,0.5);
            glPushMatrix();
            Cube cub(lat, Point(15.5-i*lat, -6, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 36
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(12.5, -1.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 24
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 6; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(15.5, -19-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 25
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,1,0);
            else
                glColor3f(0.5,0,0.5);
            glPushMatrix();
            Cube cub(lat, Point(15.5-i*lat, -17.5, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 26
    if(levelRenderMode != NIVEL2)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(11, -22-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 27
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(-2.5, -23.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 28
    for(int i = 0; i < 4; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(3.5-i*lat, -23.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 29
    for(int i = 0; i < 6; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        glPushMatrix();
        Cube cub(lat, Point(5, -16-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 30
    if(levelRenderMode == NIVEL3)
    {
        for(int i = 0; i < 7; i++)
        {
            if(i % 2 == 0)
                glColor3f(1, 0.5, 0.5);
            else
                glColor3f(0.5, 0.5, 1);
            glPushMatrix();
            Cube cub(lat, Point(3.5-i*lat, -19, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 31
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(5-i*lat, -14.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 35
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(-2.5, -10-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 32
    for(int i = 0; i < 7; i++)
    {
        if(i % 2 == 0)
            glColor3f(1,0,1);
        else
            glColor3f(0,1,1);
        glPushMatrix();
        Cube cub(lat, Point(-7, -13-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 33
    for(int i = 0; i < 4; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(-7-i*lat, -23.5, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 34
    if(levelRenderMode != NIVEL1)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i % 2 == 0)
                glColor3f(1,0,1);
            else
                glColor3f(0,1,1);
            glPushMatrix();
            Cube cub(lat, Point(-13, -20.5-i*lat, cubeCentreZ));
            cuburi.push_back(cub);
            glPopMatrix();
        }
    }

    ///zona 22
    for(int i = 0; i < 3; i++)
    {
        if(i % 2 == 0)
            glColor3f(1, 0.5, 0.5);
        else
            glColor3f(0.5, 0.5, 1);
        glPushMatrix();
        Cube cub(lat, Point(-18.5-i*lat, -9, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    ///zona 23
    for(int i = 0; i < 9; i++)
    {
        if(i % 2 == 0)
            glColor3f(0, 1, 1);
        else
            glColor3f(0, 0, 0);
        glPushMatrix();
        Cube cub(lat, Point(-17, -9-i*lat, cubeCentreZ));
        cuburi.push_back(cub);
        glPopMatrix();
    }

    return cuburi;
}
