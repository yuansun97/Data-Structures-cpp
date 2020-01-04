#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;



// helpers
  const HSLAPixel & BFS::getPixel(const Point & point) {
    return png_.getPixel(point.x, point.y);
  }

  unsigned BFS::getWidth() {
    return width_;
  }
  
  unsigned BFS::getHeight() {
    return height_;
  }

  double BFS::getTolerance() {
    return tolerance_;
  }

  bool BFS::isVisited(const Point & point) {
    return visited_[point.x][point.y];
  }

  Point BFS::getStart() {
    return start_;
  }


/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
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
  
  //std::cout << "BFS startPoint_ : (" << start_.x << ", " << start_.y << ")" << std::endl;
  queue_.push(start_);

}

BFS::~BFS() {
  
}


/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * bfs = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*bfs);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(Point(width_, height_));
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  queue_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point const top = queue_.front();
  visited_[top.x][top.y] = true;
  queue_.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if (empty()) {
    return Point(-1,-1);
  }
  return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue_.empty();
}
