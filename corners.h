#ifndef CORNERS_H
#define CORNERS_H

#include "cube.h"
#include "cross.h"

class Corners {

public:
  static void solveCorners(Cube&);
private:
  static int checkCorners(Cube&);
  static int checkBottomLayer(Cube &cube);

};

#endif
