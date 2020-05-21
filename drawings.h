#ifndef DRAWINGS_H_INCLUDED
#define DRAWINGS_H_INCLUDED

#include <vector>
#include "cube.h"

enum Textures
{
    GRASS, WATER, MARBLE, STONE
};

extern Textures textures;

void drawHuman();
std::vector<Cube> drawMaze();
void drawGround();
void drawYouWinBanner();

#endif // DRAWINGS_H_INCLUDED
