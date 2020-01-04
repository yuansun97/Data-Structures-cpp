#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


// helpers
  const HSLAPixel & DFS::getPixel(const Point & point) {
    return png_.getPixel(point.x, point.y);
  }

  unsigned DFS::getWidth() {
    return width_;
  }

  unsigned DFS::getHeight() {
    return height_;
  }

  double DFS::getTolerance() {
    return tolerance_;
  }

  bool DFS::isVisited(const Point & point) {
    return visited_[point.x][point.y];
  }

  Point DFS::getStart() {
    return start_;
  }


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) 
  : png_(png), start_(start), tolerance_(tolerance) {  
  /** @todo [Part 1] */
  width_ = png.width();
  height_ = png.height();

  // (x, y) <--> (col, row)
  visited_.resize(width_, std::vector<bool>(height_, false));

  // visited_.resize(width_);
  // for (unsigned x = 0 ; x < width_; x++) {
  //   visited_[x].resize(height_);
  //   for (unsigned y = 0; y < height_; y++) {
  //     visited_[x][y] = false;
  //   }
  // }
  
  //std::cout << "DFS startPoint_ : (" << start_.x << ", " << start_.y << ")" << std::endl;
  stack_.push(start_);
}

DFS::~DFS() {

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * dfs = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfs);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(Point(width_, height_));
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  stack_.push(point);

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  // if (empty()) {
  //   std::cout << "EMPTY!!!!!" << std::endl;
  // }
  Point const top = stack_.top();
  visited_[top.x][top.y] = true;
  stack_.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (empty()) {
    return Point(-1,-1);
  }
  return stack_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack_.empty();
}
