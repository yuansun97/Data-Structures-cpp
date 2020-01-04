#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"


ImageTraversal::~ImageTraversal() {

}


/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(const Point & endPoint) {
  /** @todo [Part 1] */
  traversal_ = NULL;
  currentPoint_.x = endPoint.x;
  currentPoint_.y = endPoint.y;
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal)
  : traversal_(&traversal) {
  /** @todo [Part 1] */
  currentPoint_ = traversal_->peek();
  tolerance_ = traversal_->getTolerance();
  start_ = traversal_->getStart();
}

ImageTraversal::Iterator::~Iterator() {
  if (traversal_ != NULL) {
    delete traversal_;
    traversal_ = NULL;
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */


// ---------------- Pop --------------

  // if (traversal_->empty()) {
  //   currentPoint_.x = traversal_->getWidth();
  //   currentPoint_.y = traversal_->getHeight();
  //   return *this;
  // }

  currentPoint_ = traversal_->pop();

// ---------------- Add --------------
  unsigned x = currentPoint_.x;
  unsigned y = currentPoint_.y;

  unsigned width = traversal_->getWidth();
  unsigned height = traversal_->getHeight();

  const Point & pRight = Point(x + 1, y);     // right point
  const Point & pDown  = Point(x, y + 1);     // down point
  const Point & pLeft  = Point(x - 1, y);     // left point
  const Point & pAbove = Point(x, y - 1);     // above point

  const HSLAPixel & pix0 = traversal_->getPixel(start_);

  // right 
  if (pRight.x < width && !traversal_->isVisited(pRight)) {
    const HSLAPixel & pix1 = traversal_->getPixel(pRight);
    double delta = ImageTraversal::calculateDelta(pix0, pix1);
    if (delta < tolerance_) {
      traversal_->add(pRight);
    }
  }

  // down
  if (pDown.y < height && !traversal_->isVisited(pDown)) {
    const HSLAPixel & pix2 = traversal_->getPixel(pDown);
    double delta = ImageTraversal::calculateDelta(pix0, pix2);
    if (delta < tolerance_) {
      traversal_->add(pDown);
    }
  }

  // left
  if (pLeft.x < width && !traversal_->isVisited(pLeft)) {
    const HSLAPixel & pix3 = traversal_->getPixel(pLeft);
    double delta = ImageTraversal::calculateDelta(pix0, pix3);
    if (delta < tolerance_) {
      traversal_->add(pLeft);
    }
  }

  // above
  if (pAbove.y < height && !traversal_->isVisited(pAbove)) {
    const HSLAPixel & pix4 = traversal_->getPixel(pAbove);
    double delta = ImageTraversal::calculateDelta(pix0, pix4);
    if (delta < tolerance_) {
      traversal_->add(pAbove);
    }
  }

  // ---------------- Peek --------------

  while (!traversal_->empty() && traversal_->isVisited(traversal_->peek())) {
    traversal_->pop();
  }

  if (traversal_->empty()) {
    currentPoint_.x = width;
    currentPoint_.y = height;
  } else {
    currentPoint_ = traversal_->peek();
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currentPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  // std::cout << "currPoint: (" << currentPoint_.x << ", " << currentPoint_.y << ")" << std::endl;
  // std::cout << "otherPoint: (" << other.currentPoint_.x << ", " << other.currentPoint_.y << ")" << std::endl;

  return !(currentPoint_ == other.currentPoint_);
}

