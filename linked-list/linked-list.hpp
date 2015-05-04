#ifndef SOUTHERD_LINKED_LIST_H_
#define SOUTHERD_LINKED_LIST_H_

#include <iostream>

namespace southerd {
  template <typename T>
  class Node {
    T data;
    Node<T>* next;
    template<class U> friend class LinkedList;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const Node<U> &rhs);

    public:
      Node(T, Node<T>*);
  };

  template <typename T>
  Node<T>::Node(T d, Node<T>* n) : data(d), next(n) {};

  template <class U>
  std::ostream& operator<<(std::ostream& out, const Node<U> &rhs){
    return out << rhs->data;
  }

  template <typename T>
  class LinkedList {
    int len;
    Node<T>* head;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<U> &rhs);

    public:
      LinkedList<T>();
      LinkedList<T>* push(T);
      Node<T>* itemAt(int);
      LinkedList<T>* pushAt(int, T);
      int length() const;
  };

  template <typename T>
  LinkedList<T>::LinkedList() : len(0), head(0x00) {};

  template <typename T>
  int LinkedList<T>::length() const {
    return this->len;
  };

  template <typename T>
  LinkedList<T>* LinkedList<T>::push(T data){
    this->head = new Node<T>(data, this->head);
#ifdef DEBUG
    std::cout << "Head is " << this->head->data << "; next is " << this->head->next << std::endl;
#endif
    this->len += 1;
    return this;
  };

  template <typename T>
  Node<T>* LinkedList<T>::itemAt(int i){
    Node<T>* item = this->head;
#ifdef DEBUG
    std::cout << "DEBUG: Head is " << item->data << std::endl;
#endif

    i -= 1; // Already at index 0.
    while(i > 0 && item->next){
      i -= 1;
      item = item->next;
    }
#ifdef DEBUG
    std::cout << "DEBUG: Found " << item->data << " at index " << i << std::endl;
#endif
    return item;
  }

  template <typename T>
  LinkedList<T>* LinkedList<T>::pushAt(int i, T data){
#ifdef DEBUG
    std::cout << "DEBUG: Adding at index " << i << " data " << data << std::endl;
#endif

    Node<T>* item = this->itemAt(i);

    item->next = new Node<T>(data, item->next);
    this->len += 1;
    return this;
  };

  template <class U>
  std::ostream& operator<<(std::ostream& out, const LinkedList<U> &rhs){
    out << rhs.length() << ": {";

    Node<U>* n = rhs.head;
    out << ' ' << n->data;
    while(n->next) {
      n = n->next;
      out << ' ' << n->data;
    };
    return out << " }";
  }
}

#endif // SOUTHERD_LINKED_LIST_H_
