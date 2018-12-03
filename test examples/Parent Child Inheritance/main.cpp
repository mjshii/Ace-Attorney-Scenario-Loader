#include <iostream>
#include <vector>
#include "headers.h"
#include <memory>

using ParentPtr = std::shared_ptr<Parent>;

int Parent::value() {
  return 0;
}

int Child::value() {
  return 1;
}

int Child2::value() {
  return 2;
}

int Child3::value() {
  return 3;
}

int getValue(ParentPtr p);
int getValue(Parent* p);

int getValue(ParentPtr p) {
  return p->value();
}

int getValue(Parent* p) {
  return getValue(ParentPtr(p));
}

int main() {
  std::vector<ParentPtr> list;
  list.push_back(ParentPtr(new Child()));
  list.push_back(ParentPtr(new Child2()));
  list.push_back(ParentPtr(new Child3()));

  std::cout << getValue(list[0]) << std::endl;
  std::cout << getValue(list[1]) << std::endl;
  std::cout << getValue(list[2]) << std::endl;
  std::cout << getValue(new Child()) << std::endl;
  std::cout << getValue(new Child2()) << std::endl;
  std::cout << getValue(new Child3()) << std::endl;
}