#ifndef FOO_CLASS_H_
#define FOO_CLASS_H_

#include <iostream>
#include <string.h>

class FooClass {
  public:
    FooClass(int size);
    ~FooClass();

    void print();
    void add_one();

  private:
    int size_m;

    float *h_data_m;
    float *d_data_m;
};

#endif // FOO_CLASS_H_
