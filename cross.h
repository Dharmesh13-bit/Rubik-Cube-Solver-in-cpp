#ifndef CROSS_H
#define CROSS_H

#include "cube.h"

class Cross {
public:
  static void solveCross(Cube&);
  static int checkCross(Cube&);
  static void solveEdge(Cube&);
};

#endif