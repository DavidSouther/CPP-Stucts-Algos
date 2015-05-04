#ifndef SOUTHERD_LINKED_LIST_H_
#define SOUTHERD_LINKED_LIST_H_

#include <iostream>
#include <assert.h>

namespace southerd {
  template <typename T>
  class Node {
    T data;
    Node<T>* next;
    template<class U> friend class LinkedList;
    template<class U> friend class LinkedListIterator;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const Node<U> &rhs);

    public:
      Node(T d, Node<T>* n) : data(d), next(n) {};
  };

  template <class U>
  std::ostream& operator<<(std::ostream& out, const Node<U> &rhs){
    return out << rhs->data;
  };

  template <typename T>
  class Iterator {
    public:
      virtual T next();
      virtual bool hasNext();
  };

  template <typename T>
  class LinkedListIterator {
    private:
      Node<T>* current;
    public:
      LinkedListIterator(Node<T>* n) : current(n) {};
      T next();
      bool hasNext() const;
  };

  template <typename T>
  T LinkedListIterator<T>::next(){
    assert(this->current);
    T ret = this->current->data;
    this->current = this->current->next;
    return ret;
  };

  template <typename T>
  bool LinkedListIterator<T>::hasNext() const {
    return this->current != 0x0;
  };

  template <typename T>
  class LinkedList {
    int len;
    Node<T>* head;
    Node<T>* tail;

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<U> &rhs);

    public:
      LinkedList<T>();
      LinkedList<T>(LinkedList<T>&);
      ~LinkedList<T>();
      LinkedList<T>* clear();
      LinkedList<T>* push(T);
      LinkedList<T>* queue(T);
      Node<T>* itemAt(int);
      Node<T>* itemBefore(T);
      LinkedList<T>* pushAt(int, T);
      LinkedList<T>* sortedInsert(T);
      LinkedList<T>* insertionSort();
      T pop();
      int length() const;
      LinkedListIterator<T>* iterator() const;
  };

  template <typename T>
  LinkedList<T>::LinkedList() : len(0), head(0x00), tail(0x00) {};

  template <typename T>
  LinkedList<T>::LinkedList(LinkedList<T>& other) : len(0), head(0x00), tail(0x00) {
    LinkedListIterator<T> iter = *(other.iterator());
#ifdef DEBUG
    std::cout << "LinkedList<T>(&other) has iterator...";
#endif
    while(iter.hasNext()){
      this->queue(iter.next());
    }
  };

  template <typename T>
  LinkedList<T>::~LinkedList<T>(){
#ifdef DEBUG
    std::cout << "Deleting LinkedList<T>" << std::endl;
#endif
    this->clear();
  }

  template <typename T>
  LinkedList<T>* LinkedList<T>::clear(){
#ifdef DEBUG
    std::cout << "Clearing LinkedList<T>" << std::endl;
#endif
    Node<T>* item = this->head;
    Node<T>* del;

    if(item){
      while(item->next){
        del = item;
        item = item->next;
        delete del;
      }
      delete item;
    }
    this->len = 0;
    this->head = this->tail = 0x00;

    return this;
  }

  template <typename T>
  int LinkedList<T>::length() const {
    return this->len;
  };

  template <typename T>
  LinkedList<T>* LinkedList<T>::push(T data){
    this->head = new Node<T>(data, this->head);
    if(this->tail == 0x0){
      this->tail = this->head;
    }

#ifdef DEBUG
    std::cout << "Head is " << this->head->data << "; next is " << this->head->next << std::endl;
#endif

    this->len += 1;
    return this;
  };

  template <typename T>
  LinkedList<T>* LinkedList<T>::queue(T data){
    Node<T>* tail = new Node<T>(data, 0x00);
    if(this->tail){
      this->tail->next = tail;
    }
    this->tail = tail;
    if(this->head == 0x0){
      this->head = tail;
    }
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
    if(this->tail == item){
      this->tail = item->next;
    }
    this->len += 1;
    return this;
  };

  template <typename T>
  T LinkedList<T>::pop(){
    assert(this->head);
    Node<T>* head = this->head;
    this->head = head->next;
    T ret = head->data;
    delete head;
    this->len -= 1;
    if(this->len == 0){
      this->tail = this->head;
    }
    return ret;
  };

  template <typename T>
  Node<T>* LinkedList<T>::itemBefore(T i){
    Node<T>* item = this->head;

    while(i > item->data && item->next && i > item->next->data){
      item = item->next;
    };

#ifdef DEBUG
    std::cout << "DEBUG: Found " << item->data << " comes before " << i << std::endl;
#endif
    return item;
  }

  template <typename T>
  LinkedList<T>* LinkedList<T>::sortedInsert(T data){
#ifdef DEBUG
    std::cout << "DEBUG: Sort Inserting " << data << std::endl;
#endif

    if(this->head == 0x0 || data < this->head->data){
      this->push(data);
    } else {
      Node<T>* previous = this->itemBefore(data);

      previous->next = new Node<T>(data, previous->next);
      if(this->tail == previous){
        this->tail = previous->next;
      }
      this->len += 1;
    }
    return this;
  };

  template <typename T>
  LinkedList<T>* LinkedList<T>::insertionSort(){
    LinkedList<T>* temp = new LinkedList<T>();
    LinkedListIterator<T>* iter = this->iterator();
    while(iter->hasNext()){
      temp->sortedInsert(iter->next());
    }
    return temp;
  };

  template <typename T>
  LinkedListIterator<T>* LinkedList<T>::iterator() const {
    return new LinkedListIterator<T>(this->head);
  };

  template <class U>
  std::ostream& operator<<(std::ostream& out, const LinkedList<U> &rhs){
    out << rhs.length() << ": {";

    LinkedListIterator<U>* iter = rhs.iterator();
    while(iter->hasNext()){
      std::cout << ' ' << iter->next();
    }

    return out << " }";
  }

}

#endif // SOUTHERD_LINKED_LIST_H_
