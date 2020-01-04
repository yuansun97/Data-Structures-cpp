#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stack>
#include <algorithm>
#include <iostream>

#pragma once

using namespace cs225;

class SquareMaze {
    public:
    /**
     * No-parameter constructor
     * */
    SquareMaze();

    /**
     * Determine whether it is possible to travel in the given
     * direction from the square at coordinates (x, y).
     * 
     * The origin of the coordinate is at the top-left point, 
     * with x-axis pointing to the right, y-axis to the down.
     * 
     * dir = 0: rightward step (+1 to the x coordinate)
     * dir = 1: downward step  (+1 to the y coordinate)
     * dir = 2: leftward step  (-1 to the x coordinate)
     * dir = 3: upward step    (-1 to the y coordinate)
     * 
     * @param x The x coordinate of current cell
     * @param y The y coordinate of current cell
     * @param dir The desired direction to move from the current cell
     * @return whther the specified direction can be traveled
     * */
    bool canTravel(int x, int y, int dir) const;

    /**
     * 
     * */
    PNG * drawMaze() const;

    /**
     * 
     * */
    PNG * drawMazeWithSolution();

    /**
     * Makes a new SquareMaze 
     * (with square cells, the maze itself not have to a square) 
     * of the given height and width.
     * 
     * If this object already represents a maze 
     * it will clear all the existing data before doing so. 
     * 
     * Randomly select walls to delete without creating a cycle,
     * until there are no more walls that could be deleted. 
     * Walls on the perimeter should not be deleted.
     * 
     * @param width	 The width of the SquareMaze (number of cells)
     * @param height The height of the SquareMaze (number of cells)
     * */
    void makeMaze(int width, int height);

    /**
     * @param x	The x coordinate of the current cell
     * @param y	The y coordinate of the current cell
     * @param dir	Either 0 (right) or 1 (down) specifying which wall to set. 
     *              Only support setting the bottom and right walls 
     *              of every square in the grid.
     * @param exists	true if setting the wall to exist, false otherwise
     * */
    void setWall(int x, int y, int dir, bool exists);

    /**
     * 
     * */
    std::vector<int> solveMaze();

    PNG * drawCreativeMaze();

    private:

    // Maze's width and height
    int _width;
    int _height;

    int _destination;
    std::vector<int> _solution;

    /**
     * Class point stores whether or not the point 
     * connect to its right/down
     * */
    class point {
        public:
        bool can_go_right = false;
        bool can_go_down = false;
    };

    /**
     * A 1-D vector representing a 2-D maze by storing points' walls
     * 
     * A point (x, y) in the maze corresponds 
     * to maze_in_vec[y * width + x]
     * */
    std::vector<point> maze_in_vec;

    /**
     * A disjoint set storing the connectivity between points
     * */
    DisjointSets _dset;

    /**
     * Setunion for two points. 
     * 
     * @param x	    The x coordinate of the current cell
     * @param y	    The y coordinate of the current cell
     * @param dir	Either 0 (right) or 1 (down) specifying 
     *                  which point to connect. 
     * @return true  If the two points were not connected before,
     *               that is, in the same set/uptree.
     *         false If the two points are already connected
     * */
    bool setConnectivity(int x, int y, int dir);
};