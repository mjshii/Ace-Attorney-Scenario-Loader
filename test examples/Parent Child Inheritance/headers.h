class Parent {
public:
  virtual int value();
};

class Child : public Parent {
public:
  int value();
};

class Child2 : public Parent {
public:
  int value();
};

class Child3 : public Child {
public:
  int value();
};