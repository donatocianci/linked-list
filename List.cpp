/**
 * Simple linked-list, templated class.
 *
 * @author
 *   Donato Cianci
 */

#include "List.h"


template <typename T>
const T & List<T>::peekFront() const {
  if (!head_) {
    throw std::runtime_error("peekFront() called on empty List");
  }
  return head_->data;
}

template <typename T>
List<T> List<T>::mergeSort() {
  // Returns a copy of the list that is sorted using the merge sort algorithm.

  if (length_ <= 1) {
    return *this;
  }

  List left;
  List right = *this;



  int half = length_ / 2;

  for (int i=0; i<half; i++) {
    T leftmost = right.peekFront();
    left.insertAtBack(leftmost);
    right.popFront();

    }



  left = left.mergeSort();
  right = right.mergeSort();

  return merge(left, right);

  }


template <typename T>
void List<T>::insertAtBack(const T & data) {

  Node *node = new Node(data);

  if (length_==0) {
    head_ = node;
    tail_ = node;
  }

  else {
    tail_->next = node;
    tail_ = node;
  }

  length_++;

}

template <typename T>
void List<T>::insertAtFront(const T & data) {

  Node *node = new Node(data);


  node->next = head_;

  head_ = node;
  if (length_==0) {
    tail_ = node;
  }
  length_++;
}

template <typename T>
List<T> merge(const List<T> & leftList, const List<T> & rightList) {

  List<T> left = leftList;
  List<T> right = rightList;

  List<T> *merged = new List<T>;

  while(!left.is_empty() && !right.is_empty()) {
    if ( left.peekFront() <= right.peekFront() ) {
      (*merged).insertAtBack(left.peekFront());
      left.popFront();
    }
    else {
      (*merged).insertAtBack(right.peekFront());
      right.popFront();
    }

  }

  while(!left.is_empty()) {
    (*merged).insertAtBack(left.peekFront());
    left.popFront();
  }
  while(!right.is_empty()) {
    (*merged).insertAtBack(right.peekFront());
    right.popFront();
  }
  return *merged;
}

/**
 * Finds and returns the Node containing `data` in the
 * List or `nullptr` if the data is not found.
 */
template <typename T>
typename List<T>::Node *List<T>::_find(const T & data) {
  Node *cur = head_;
  while (cur != nullptr) {
    if (cur->data == data) { return cur; }
    cur = cur->next;
  }

  return nullptr;
}

template <typename T>
void List<T>::popFront() {
  //deletes the front element in the linked list

  if (!head_) return;

  if (!head_->next) {

    delete head_;

    head_ = nullptr;
    tail_ = nullptr;

    length_--;
    return;
  }

  Node* oldHead = head_;
  // Update head_
  head_ = head_->next;

  delete oldHead;

  oldHead = nullptr;

  // update size
  length_--;
}
