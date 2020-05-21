#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include "cube.h"

enum Levels
{
    NIVEL1, NIVEL2, NIVEL3
};

enum Coordinates
{
    X, Y, Z, W
};

enum Coefficients
{
    A, B, C, D
};

enum Shadow{
    SHADOW, NOSHADOW
};

extern Levels levels;
extern Coordinates coordinates;
extern Coefficients coefficients;
extern Shadow shadows;

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4

bool checkCollision(Cube cub1, Cube cub2);
bool checkAllCollisions(Cube player, std::vector<Cube> cuburi);
GLuint LoadTexture(const char* filename);

void shadowmatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);
void findplane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);

void levelMenu(int selection);
void textureMenu(int selection);
void shadowMenu(int selection);

#endif // UTILS_H_INCLUDED
