#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <vector>
#include "cube.h"

enum Levels
{
    NIVEL1, NIVEL2, NIVEL3
};

extern Levels levels;

void drawHuman();
std::vector<Cube> drawMaze();
bool checkCollision(Cube cub1, Cube cub2);
bool checkAllCollisions(Cube player, std::vector<Cube> cuburi);
GLuint LoadTexture(const char* filename);



#endif // UTILS_HPP_INCLUDED



#endif // UTILS_H_INCLUDED
