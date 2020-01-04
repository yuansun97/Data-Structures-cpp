#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze maze;
    maze.makeMaze(100, 100);
    PNG * png = maze.drawCreativeMaze();
    png->writeToFile("creative.png");

    delete png;
    return 0;
}
