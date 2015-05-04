#include <iostream>

#include "linked-list.hpp"

inline void BuildOneTwoThree(southerd::LinkedList<int>* list){
  list->push(3)->push(2)->push(1);
}

int main() {
  southerd::LinkedList<int> list, sortedList;

  std::cout << list << std::endl;

  BuildOneTwoThree(&list); // Start with {1, 2, 3}
  std::cout << list << std::endl;
  list.push(13); // Push 13 on the front, yielding {13, 1, 2, 3}

  std::cout << list << std::endl;

  list.pushAt(1, 42);

  std::cout << list << std::endl;

  std::cout << "Iterating... ";
  southerd::LinkedListIterator<int>* iter = list.iterator();
  while(iter->hasNext()){
    std::cout << iter->next() << ' ';
  }
  delete iter;
  std::cout << std::endl;

  sortedList = *(list.insertionSort());
  std::cout << sortedList << std::endl;

  int top = list.pop();
  std::cout << "(" << top << ") " << list << std::endl;

  list.clear();

  std::cout << list << std::endl;

  return 0;
}
