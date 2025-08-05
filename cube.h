#ifndef CUBE_H
#define CUBE_H

#include <iostream>
using namespace std;
class Cube {

  public: int cubes[9][6];

  public: Cube(bool);
  private: void scramble();

  public:
  void moves(string);
  void output();
  void R(int);
  void L(int);
  void U(int);
  void D(int);
  void F(int);
  void B(int);
};
#endif
