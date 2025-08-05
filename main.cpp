#include "cube.h"
#include "cross.h"
#include "corners.h"
#include "edges.h"
#include "OLL.h"
#include "PLL.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


string format(string);

int main(int argc, char **argv) {

  Cube myCube(false);
    int scrambleNum = 0;
    string argString;
    while (getline(cin, argString)) {
    ++scrambleNum;
    string scramble = format(argString);
    cout << "Scramble #" << scrambleNum << ": ";
    myCube.moves(scramble);
    myCube.output();
    Cross::solveCross(myCube);
    cout << "Cross solved" << endl;
      myCube.output();
    Corners::solveCorners(myCube);
    cout << "Corners solved" << endl;
    myCube.output();
    Edges::solveEdges(myCube);
    cout << "Edges solved" << endl;
    myCube.output();
    OLL::solveOLL(myCube);
    cout << "OLL solved" << endl;
    myCube.output();
    PLL::solvePLL(myCube);
    cout << "PLL solved" << endl;
      myCube.output();
  }
  return 0;
}

string format(string s) {
  string formatted;

  for (int i=0; i<s.length(); ++i) {
    if (s[i] == '\'') {
      formatted += s[i-1];
      formatted += s[i-1];
    }
    else if (s[i] == '2') {
      formatted += s[i-1];
    }
    else if (s[i] == ' ') {

    }
    else {
      formatted += s[i];
    }
  }

  return formatted;
}
