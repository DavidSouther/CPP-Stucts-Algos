#include <iostream>

#include "linked-list.hpp"

inline void BuildOneTwoThree(southerd::LinkedList<int>* list){
  list->push(3)->push(2)->push(1);
};

southerd::LinkedList<int>* BuildOneTwoThree(){
  southerd::LinkedList<int>* list = new southerd::LinkedList<int>();
  BuildOneTwoThree(list);
  return list;
};

void SplitAndPrint(southerd::LinkedList<int>* list){
  southerd::LinkedList<int>** splits = list->split();
  southerd::LinkedList<int>* a = splits[0];
  southerd::LinkedList<int>* b = splits[1];
  std::cout << *a << std::endl;
  std::cout << *b << std::endl;
  delete a;
  delete b;
  delete splits;
};

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

  SplitAndPrint(&list);
  int one[] = {1, 0x00};
  list.pushAll(one);
  std::cout << list << std::endl;
  SplitAndPrint(&list);
  int two[] = {1, 2, 0x00};
  list.clear()->pushAll(two);
  SplitAndPrint(&list);
  SplitAndPrint(BuildOneTwoThree());
  SplitAndPrint(&sortedList);


  return 0;
}
