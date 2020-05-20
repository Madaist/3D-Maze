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
