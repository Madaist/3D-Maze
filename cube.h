#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "point.h"
#include <GL/glut.h>
#include <vector>

class Cube
{
public:
    Point centre;
    float size;

    void drawCube()
    {
        glPushMatrix();
        glTranslated(centre.x, centre.y, centre.z);
        glutSolidCube(size);
        glPopMatrix();
    }

    Cube(float size, Point centre)
    {
        this->size = size;
        this->centre = centre;
        this->drawCube();
    }

};


#endif // CUBE_H_INCLUDED
