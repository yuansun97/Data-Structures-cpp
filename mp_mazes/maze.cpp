#include "maze.h"

/**
 * No-parameter constructor
 * */
SquareMaze::SquareMaze() {

}

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
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    int idx = y * _width + x;
    switch (dir) {
        case 0: {
            // rightward
            return maze_in_vec[idx].can_go_right;
            break;
        }
        case 1: {
            // downward
            return maze_in_vec[idx].can_go_down;
            break;
        }
        case 2: {
            // leftward
            if (x == 0) return false;
            return maze_in_vec[idx - 1].can_go_right;
            break;
        }
        case 3:{
            // upward
            if (y == 0) return false;
            return maze_in_vec[idx - _width].can_go_down;
            break;
        }    
    }
    return false;
}


PNG * SquareMaze::drawMaze() const {
    PNG * png = new PNG(_width * 10 + 1, _height * 10 + 1);
    // blacken topmost row except the entrance
    for (int i = 10; i < _width * 10 + 1; i++) {
        HSLAPixel & p = png->getPixel(i, 0);
        p.l = 0;
    }
    // blacken leftmost column
    for (int j = 0; j < _height * 10 + 1; j++) {
        HSLAPixel & p = png->getPixel(0, j);
        p.l = 0;
    }
    // blacken inner walls
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int idx = y * _width + x;
            if (!maze_in_vec[idx].can_go_right) {
                // draw right wall
                int png_x = x * 10 + 10;
                int png_y = y * 10;
                for (int k = 0; k < 11; k++) {    
                    HSLAPixel & p = png->getPixel(png_x, png_y + k);
                    p.l = 0;
                }
            }
            if (!maze_in_vec[idx].can_go_down) {
                // draw down wall
                int png_x = x * 10;
                int png_y = y * 10 + 10;
                for (int k = 0; k < 11; k++) {
                    HSLAPixel & p = png->getPixel(png_x + k, png_y);
                    p.l = 0;
                }
            }
        }
    }
    return png;
}


PNG * SquareMaze::drawMazeWithSolution() {
    PNG * png = drawMaze();
    if (_solution.empty()) {
        solveMaze();
    }

    // std::cout << "solution: ";
    // for (const auto & dir : _solution) {
    //     std::cout << dir << ", ";
    // }
    
    // std::cout << std::endl;
    int png_x = 5;
    int png_y = 5;
    // Draw solution path
    for (const auto & dir : _solution) {
        if (dir == 0) {
            // right
            for (int k = 0; k < 11; k++) {
                HSLAPixel & p = png->getPixel(png_x + k, png_y);
                p.h = 0;
                p.s = 1;
                p.l = 0.5;
                p.a = 1;
            }
            png_x += 10;
        } else if (dir == 1) {
            // down
            for (int k = 0; k < 11; k++) {
                HSLAPixel & p = png->getPixel(png_x, png_y + k);
                p.h = 0;
                p.s = 1;
                p.l = 0.5;
                p.a = 1;
            }
            png_y += 10;
        } else if (dir == 2) {
            // left
            for (int k = 0; k < 11; k++) {
                
                // std::cout << "(" << png_x - k << ", " << png_y << ")" << std::endl;

                HSLAPixel & p = png->getPixel(png_x - k, png_y);
                p.h = 0;
                p.s = 1;
                p.l = 0.5;
                p.a = 1;
            }
            png_x -=10;
        } else if (dir == 3) {
            // up
            for (int k = 0; k < 11; k++) {

                // std::cout << "(" << png_x << ", " << png_y - k << ")" << std::endl;

                HSLAPixel & p = png->getPixel(png_x, png_y - k);
                p.h = 0;
                p.s = 1;
                p.l = 0.5;
                p.a = 1;
            }
            png_y -= 10;
        }
    }
    // Whiten the exit
    int y = _destination / _width;
    int x = _destination % _width;
    png_x = x * 10;
    png_y = y * 10 + 10;
    for (int k = 1; k < 10; k++) {
        HSLAPixel & p = png->getPixel(png_x + k, png_y);
        p.l = 1;
    }
	return png;
}

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
void SquareMaze::makeMaze(int width, int height) {
    // Clear and initialize
    _solution.clear();
    _width = width;
    _height = height;
    int size = width * height;
    maze_in_vec.clear();
    maze_in_vec.resize(size);
    _dset.clearDSet();
    _dset.addelements(size);

    // Randomly delete walls
    // usleep(1);
    // srand(time(NULL));
    while (_dset.size(0) < size) {      
        // Delete walls until there is only one set (uptree),
        // that is, the set (uptree) size equals to maze size.
        int rand_x = rand() % _width;
        int rand_y = rand() % _height;
        int rand_dir = rand() % 2;
        int idx = rand_y * width + rand_x;
        if (setConnectivity(rand_x, rand_y, rand_dir)) {
            setWall(rand_x, rand_y, rand_dir, 0);
        }
    }
}

/**
 * @param x	The x coordinate of the current cell
 * @param y	The y coordinate of the current cell
 * @param dir	Either 0 (right) or 1 (down), which specifies which wall to set. 
 *              Only support setting the bottom and right walls of every square in the grid.
 * @param exists	true if setting the wall to exist, false otherwise
 * */
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        int idx = y * _width + x;
        if (dir == 0 && x < _width - 1) {
            // right wall
            maze_in_vec[idx].can_go_right = !exists;
        } else if (dir == 1 && y < _height - 1) {
            // down wall
            maze_in_vec[idx].can_go_down = !exists;
        }
    }
}


std::vector<int> SquareMaze::solveMaze() {
    int size = _height * _width;
    // path store the former point to get the current index point
    std::vector<int> path;
    std::vector<bool> visited;
    std::vector<int> distance;
    path.resize(size);
    visited.resize(size);
    distance.resize(size); 

    std::stack<int> dfs;
    dfs.push(0);
    path[0] = -1;
    distance[0] = 0;

    // traversal
    // std::cout << "dfs: ";
    while (!dfs.empty()) {
        // ------ pop ------
        int curr_idx = dfs.top();

        // std::cout << curr_idx << ",";

        visited[curr_idx] = true;
        dfs.pop();
        int curr_x = curr_idx % _width;
        int curr_y = curr_idx / _width;

        // ------ add ------
        int next_idx;

        // std::cout << "currIdx: " << curr_idx << std::endl;
        // Right
        if (canTravel(curr_x, curr_y, 0)) {
            next_idx = curr_idx + 1;
            if (!visited[next_idx]) {
                dfs.push(next_idx);
                path[next_idx] = curr_idx;
                distance[next_idx] = distance[curr_idx] + 1;
            }
        }
        // Down
        if (canTravel(curr_x, curr_y, 1)) {
            next_idx = curr_idx + _width;
            if (!visited[next_idx]) {
                dfs.push(next_idx);
                path[next_idx] = curr_idx;
                distance[next_idx] = distance[curr_idx] + 1;
            }
        }
        // Left
        if (canTravel(curr_x, curr_y, 2)) {
            next_idx = curr_idx - 1;
            if (!visited[next_idx]) {
                dfs.push(next_idx);
                path[next_idx] = curr_idx;
                distance[next_idx] = distance[curr_idx] + 1;
            }
        }
        // Up
        if (canTravel(curr_x, curr_y, 3)) {
            next_idx = curr_idx - _width;
            if (!visited[next_idx]) {
                dfs.push(next_idx);
                path[next_idx] = curr_idx;
                distance[next_idx] = distance[curr_idx] + 1;
            }
        }
        

        // ------ peek ------
        while (!dfs.empty() && visited[dfs.top()]) {
            dfs.pop();
        }
    }

    // std::cout << std::endl << "-- dfs finished --" << std::endl;
    // std::cout << "path: ";
    // for (const auto & point : path) {
    //     std::cout << point << ", ";
    // }
    // std::cout << std::endl << "distance: ";
    // for (const auto & dis : distance) {
    //     std::cout << dis << ", ";
    // }
    // std::cout << std::endl;

    // After traversal
    // Pick the destination point that has longest distance from the origin
    int dest_idx = size - _width;
    int max_dist = distance[dest_idx];
    for (int i = 1; i < _width; i++) {
        int tmp = size - _width + i;
        if (max_dist < distance[tmp]) {
            max_dist = distance[tmp];
            dest_idx = tmp;
        }
    }

    // Track back the longest path and store the solution
    _destination = dest_idx;

    // std::cout << "destination: " << _destination << std::endl;

    int idx = dest_idx;
    std::vector<int> solution;
    while (path[idx] >= 0 ) {
        int prev = path[idx];
        if (prev == idx + 1) {
            // right
            solution.push_back(2);
        } else if (prev == idx - 1) {
            // left
            solution.push_back(0);

        } else if (prev == idx + _width) {
            // down
            solution.push_back(3);

        } else if (prev == idx - _width) {
            // up
            solution.push_back(1);
        }
        idx = prev;
    }
    std::reverse(solution.begin(), solution.end());
    _solution.assign(solution.begin(), solution.end());

    return solution;
}

/**
 * Setunion for two points.
 * 
 * @param x	    The x coordinate of the current cell
 * @param y	    The y coordinate of the current cell
 * @param dir	Either 0 (right) or 1 (down) specifying 
 *                  which point to connect. 
 * 
 * @return true  If the two points were not connected before,
 *               that is, in the same set/uptree.
 *         false If the two points are already connected
 * */
bool SquareMaze::setConnectivity(int x, int y, int dir) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        int idx = y * _width + x;
        if (dir == 0 && x < _width - 1) {
            // connect right point
            if (_dset.find(idx) != _dset.find(idx + 1)) {
                _dset.setunion(idx, idx + 1);
                return true;
            }
        } else if (dir == 1 && y < _height - 1) {
            // connect down point
            if (_dset.find(idx) != _dset.find(idx + _width)) {
                _dset.setunion(idx, idx + _width);
                return true;
            }
        }
    }
    return false;
}

PNG * SquareMaze::drawCreativeMaze() {
    PNG * png = drawMaze();

    return png;
}