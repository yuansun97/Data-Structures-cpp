template <class T>
int List<T>::size() const {
    return length_;
}

template <class T>
List<T>::List(List<T> const& other) {
    _copy(other);
}

template <class T>
List<T>& List<T>::operator=(List<T> const& rhs) {
    if (this != &rhs) {
        _destroy();
        _copy(rhs);
    }
    return *this;
}

template <class T>
bool List<T>::empty() const {
    return head_ == NULL && tail_ == NULL && length_ == 0;
}

template <class T>
void List<T>::_copy(List<T> const& other) {

  this->head_ = NULL;
  this->tail_ = NULL;
  this->length_ = 0;

  if (other.length_ == 0) {
    return;
  }

  this->head_ = new ListNode(other.head_->data);
  ListNode * tmp1 = this->head_;
  ListNode * tmp2 = other.head_;

  for (int i = 1; i < other.length_; i++) {
    tmp1->next = new ListNode(tmp2->next->data);
    tmp1->next->prev = tmp1;
    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }

  this->tail_ = tmp1;

  this->length_ = other.length_;

}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  _destroy();
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

template <class T>
void List<T>::print(ostream& os) const {
    os << "<";
    ListNode* curr = head_;
    while (curr != NULL) {
        os << " " << curr->data;
        curr = curr->next;
    }
    os << " >";
}

// overloaded operator<<
template <class T>
ostream& operator<<(ostream& os, const List<T>& list) {
    list.print(os);
    return os;
}

// ListNode constructors
template <class T>
List<T>::ListNode::ListNode() : next(NULL), prev(NULL), data(T())
{ /* nothing */ }

template <class T>
List<T>::ListNode::ListNode(const T& ndata) : next(NULL), prev(NULL), data(ndata)
{ /* nothing */ }

template <class T>
template <class Iter>
List<T>::List(const Iter& begin_iterator, const Iter& end_iterator)
    : head_(NULL), tail_(NULL), length_(0)
{
    for (Iter i = begin_iterator; i != end_iterator; ++i)
        insertBack(*i);
}
