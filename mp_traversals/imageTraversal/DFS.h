/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  ~DFS();

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  // helpers
  const HSLAPixel & getPixel(const Point & point);
  unsigned getWidth();
  unsigned getHeight();
  double getTolerance();
  bool isVisited(const Point & point);
  Point getStart();

private:
	/** @todo [Part 1] */
	/** add private members here*/
  const PNG png_;
  const Point start_;
  const double tolerance_;
  std::vector<std::vector<bool>> visited_;
  unsigned width_;
  unsigned height_;
  std::stack<Point> stack_;
};
