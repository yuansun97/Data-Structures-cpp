/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return (first[curDim] == second[curDim]) ? first < second : first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    unsigned currDistance = 0;
    unsigned poteDistance = 0;
    for (unsigned i = 0; i < Dim; i++) {
      currDistance += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      poteDistance += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    return (currDistance == poteDistance) ? potential < currentBest : poteDistance < currDistance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) {
      root = NULL;
      size = 0;
      return;
    }

    vector<Point<Dim>> points(newPoints);
    size = 0;
    // buildTree(newPoints, level, *& subroot, start, end)
    buildTree(points, 0, root, 0, points.size() - 1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(root, other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
    _clear(root);
    _copy(root, rhs.root);
  }
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    unsigned level = 0;
    Point<Dim> currBest = root->point;
    findNearest(root, level, currBest, query);
    return currBest;
}



// Helper functions
template <int Dim>
void KDTree<Dim>::swap(vector<Point<Dim>> & points, unsigned first, unsigned second) 
{
  if (points.size() == 0 || first == second) {
    return;
  }
  Point<Dim> tmp = points[first];
  points[first] = points[second];
  points[second] = tmp;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>> & newPoints, unsigned start, 
                                    unsigned end, unsigned pivotIdx, unsigned d) 
{
  Point<Dim> pivot = newPoints[pivotIdx];
  swap(newPoints, end, pivotIdx);   // move the pivot to the end
  unsigned flagIdx = start;
  for (unsigned i = start; i < end; i++) {
    if (smallerDimVal(newPoints[i], pivot, d)) {
      swap(newPoints, i, flagIdx);
      flagIdx++;
    }
  }
  swap(newPoints, flagIdx, end);    // the pivot is in the end index
  return flagIdx;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>> & newPoints, unsigned start, 
                                          unsigned end, unsigned k, unsigned d) 
{
  if (start == end) {
    return newPoints[start];
  }
  unsigned pivotIdx = (start + end) / 2;
  pivotIdx = partition(newPoints, start, end, pivotIdx, d);
  if (pivotIdx == k) return newPoints[pivotIdx];
  // select in the left half
  if (pivotIdx > k) return select(newPoints, start, pivotIdx - 1, k, d);
  // select in the right half
  else return select(newPoints, pivotIdx + 1, end, k, d);
}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>> & newPoints, unsigned level, 
                            KDTree<Dim>::KDTreeNode *& subroot, unsigned start, unsigned end) 
{
  // unsigned end from last rescursion might be larger than the vector size
  // (eg, last unsigned mid = 0, then unsigned end = mid - 1 = MAX_)
  // or less than the start
  if (this->size == newPoints.size() || end < start || end >= newPoints.size()) {
    return;
  }
  unsigned mid = (start + end) / 2;
  Point<Dim> midPoint = select(newPoints, start, end, mid, level % Dim);
  subroot = new KDTreeNode(midPoint);
  size++;
  level++;
  // build left subtree
  buildTree(newPoints, level, subroot->left, start, mid - 1);
  // build right subtree
  buildTree(newPoints, level, subroot->right, mid + 1, end);
}

template<int Dim>
void KDTree<Dim>::_copy(KDTree<Dim>::KDTreeNode *& currRoot, const KDTree<Dim>::KDTreeNode *& otherRoot) {
  if (otherRoot == NULL) {
    currRoot = NULL;
    return;
  }
  currRoot = new KDTree<Dim>::KDTreeNode(otherRoot->point);
  _copy(currRoot->left, otherRoot->left);
  _copy(currRoot->right, otherRoot->right);  
}

template<int Dim>
void KDTree<Dim>::_clear(KDTree<Dim>::KDTreeNode * subroot) {
	if (subroot == NULL) return;
	_clear(subroot->left);
	_clear(subroot->right);
	delete subroot;
	subroot = NULL;
  //size--;
}

template <int Dim>
void KDTree<Dim>::findNearest(KDTreeNode * subroot, unsigned level, Point<Dim> & currBest,
                              const Point<Dim>& query) const
{
  if (subroot == NULL) return;
  Point<Dim> currPoint = subroot->point;
  /** Base case
    * Return currPoint, if subroot is leaf or currPoint is the same to query
    **/
  if ((subroot->left == NULL && subroot->right == NULL)
        || currPoint == query) {
    if (shouldReplace(query, currBest, currPoint)) {
      currBest = currPoint;
    }
    return;
  }
  /** Recursion
   *  Binary K-d search
   * */
  bool goLeft = smallerDimVal(query, currPoint, level % Dim);
  level++;
  if (goLeft) {
    findNearest(subroot->left, level, currBest, query);
  } else {
    findNearest(subroot->right, level, currBest, query);
  }
  // Track back: check if need repace with the current subroot
  level--;  // track back, recover the level
  if (shouldReplace(query, currBest, currPoint)) {
    currBest = currPoint;
  }
  // Check if need to traverse the other branch (visually, the intersection region within the radius)
  // Only when the subroot is tangent to the circle/sphere there is no intersection,
  // that is, no need to traverse to the other branch.


  Point<Dim> boundPoint = query;
  boundPoint[level % Dim] = currPoint[level % Dim];
  // shouldReplace(target, currentBest, potential)

  if (shouldReplace(query, currBest, boundPoint)) {
    level++;
    if (goLeft) {
      findNearest(subroot->right, level, currBest, query);
    } else {
      findNearest(subroot->left, level, currBest, query);
    }
  }
}