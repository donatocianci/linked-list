/**
 * Simple Linked-list, templated class.
 *
 * @author
 *   Donato Cianci
 */

#pragma once
#include <iostream> // for std::cerr, std::cout
#include <ostream> // for std::ostream

// need to create deep copy.

template <typename T>
class List {
  public:

    const T& peekFront() const;
    void insertAtFront(const T & data);
    void insertAtBack(const T & data);
    List<T> mergeSort();
    void popFront();
    bool is_empty() const;
    bool equals(const List<T> other) const;

    bool operator==(const List<T>& other) const {
      return equals(other);
    }
    bool operator!=(const List<T>& other) const {
      return !equals(other);
    }


    // Delete all items in the list, leaving it empty.
    void clear() {
      while (head_) {
        popFront();
      }

    }

    List<T>& operator=(const List<T>& other) {
      // Clear the current list.
      clear();

      const Node* cur = other.head_;
      while (cur) {
        insertAtBack(cur->data);
        cur = cur->next;
      }

      return *this;
    }

    //Redefine copy constructor to use deep copy
    List(const List<T>& other) : List() {
      *this = other;
    }

    //ensure that  head_ is null-initialized.
    List() : head_(nullptr), tail_(nullptr), length_(0) { }


    ~List() {

      clear();

    }

    // Output a string representation of the list.
    // This requires that the data type T supports stream output itself.
    // This is used by the operator<< overload defined in this file.
    std::ostream& print(std::ostream& os) const;

  private:
    class Node {
      public:
        //Note: this creates an actual data item that this node contains.
        //So passing a reference will still create a new data item.
        T data;
        Node *next;
        Node(const T & data) : data(data), next(nullptr) { }

        //Redefine copy with equals to get deep copy
        Node& operator=(const Node& other) {
          data = other.data;
          next = other.next;

          return *this;
        }

        //Redefine copy constructor to use deep copy
        Node(const Node& other) : next(other.next), data(other.data) { }

        ~Node() {}

    };

    // Even though this is defined after being used at the top, that's OK when
    // defined in a class.
    Node *head_;

    Node *tail_;

    int length_;

    Node* _find(const T & data);


};


template <typename T>
bool List<T>::is_empty() const {

  if (length_ == 0) return true;
  else return false;

}

template <typename T>
std::ostream & operator<<(std::ostream& os, const List<T>& list) {
  return list.print(os);
}

template <typename T>
std::ostream & List<T>::print(std::ostream& os) const {
  // List format will be [(1)(2)(3)], etc.
  os << "[";

  // Note that this works correctly for an empty list.
  Node* cur = head_;
  while (cur) {
    os << "(" << cur->data << ")";
    cur = cur->next;
  }

  os << "]";

  return os;
}

template <typename T>
bool List<T>::equals(const List<T> other) const {

  if (length_ != other.length_) {
    return false;
  }

  const Node* cur = head_;
  const Node* otherCur = other.head_;

  while (cur){
    if (!otherCur) {
      throw std::runtime_error("wrong item count since otherCur missing node");
    }
    if (cur->data != otherCur->data) {
      return false;
    }
    cur = cur->next;
    otherCur = otherCur->next;
  }
  return true;
}



#include "List.cpp"
