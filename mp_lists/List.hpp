/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode * tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;

  if (tail_ != NULL) {
    tail_->next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  tail_ = newNode;

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint == 0) {
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (length_ < 3) {
    return;
  }


  
  ListNode * curr = head_;
  while (curr->next != NULL && curr->next != tail_) {
    tail_->next = curr->next;
    tail_->next->prev = tail_;
    tail_ = tail_->next;
    curr->next = tail_->next;
    tail_->next->prev = curr;
    tail_->next = NULL;

    curr = curr->next;
  }
  

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if (startPoint == NULL || endPoint == NULL) {
    return;
  }

  if (startPoint == endPoint) {
    return;
  }

  if (startPoint->prev != NULL) {
    startPoint->prev->next = endPoint;
  }
  if (endPoint->next != NULL) {
    endPoint->next->prev = startPoint;
  }

  // startPoint->next = endPoint->next;
  // endPoint->next = startPoint;

  ListNode * curr = startPoint;
  startPoint = endPoint;      // the new startPoint
  endPoint = curr;            // the new endPoint

  ListNode * seconNode = curr->next;
  curr = seconNode;          // start from the second node

  ListNode * tmp;
  while (curr != startPoint) {  // the current startPoint is actually the original endPoint
    tmp = curr->next;
    curr->next = curr->prev;
    curr->prev = tmp;

    curr = tmp;
  }

  //  change the startPoint's and endPoint' next/prev pointers
  tmp = startPoint->next;
  startPoint->next = startPoint->prev;  // the current startPoint is actually the original endPoint
  startPoint->prev = endPoint->prev;
  endPoint->next = tmp;
  endPoint->prev = seconNode;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  ListNode * groupStart = head_;
  ListNode * groupEnd = groupStart;
  while (groupStart != NULL) {

    // find the end of the current group of N-nodes
    for (int i = 0; i < n - 1; i++) {
      if (groupEnd->next == NULL) {
        break;
      }
      groupEnd = groupEnd->next;
    }

    //ListNode * nextStart = groupEnd->next;
    // feed start and end into reverse function

    if (groupStart == head_) {
      head_ = groupEnd;
    }
    if (groupEnd == tail_) {
      tail_ = groupStart;
    }
    reverse(groupStart, groupEnd);

    
    groupStart = /*nextStart*/ groupEnd->next;
    groupEnd = groupStart;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}



/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (second == NULL) {
    return first;
  }

  if (first == NULL) {
    return second;
  }

  ListNode * ret;

  if (second->data < first->data) {
    ret = second;
    second = second->next;
  } else {
    ret = first;
    first = first->next;
  }

  ListNode * tmp = ret;
  while (first != NULL && second != NULL) {
    if (second->data < first->data) {
      second->prev = tmp;
      tmp->next = second;

      second = second->next;
    } else {
      first->prev = tmp;
      tmp->next = first;

      first = first->next;
    }

    tmp = tmp->next;
  }

  if (first == NULL && second != NULL) {
    second->prev = tmp;
    tmp->next = second;
  }

  if (first != NULL && second == NULL) {
    first->prev = tmp;
    tmp->next = first;
  }

  return ret;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if (chainLength <= 1) {
    return start;
  }

  int len = chainLength / 2;

  ListNode * second = split(start, len);

  return merge(mergesort(start, len), mergesort(second, chainLength - len));
}
