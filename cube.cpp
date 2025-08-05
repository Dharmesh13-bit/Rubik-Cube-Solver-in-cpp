#include "cube.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Cube::Cube(bool scrambled) {

  for (int sticker=0; sticker<9; ++sticker) {
    for (int side=0; side<6; ++side) {
      if (side==0) {
        Cube::cubes[sticker][side] = 0; //White
      }
      else if(side==1) {
        Cube::cubes[sticker][side] = 1; //Yellow
      }
      else if(side==2) {
        Cube::cubes[sticker][side] = 2; //Red
      }
      else if(side==3) {
        Cube::cubes[sticker][side] = 3; //Green
      }
      else if(side==4) {
        Cube::cubes[sticker][side] = 4; //Orange
      }
      else if(side==5) {
        Cube::cubes[sticker][side] = 5; //Blue
      }
    }
  }

  if (scrambled) {
    Cube::scramble();
  }
}
void Cube::moves(std::string sequence) {
  string outputSequence = "";
  int sequenceLength = sequence.length();
  for (int i=0; i<sequenceLength; ++i) {
    bool validMove = true;
    switch (sequence[i]) {
      case 'U':
        U(1);
        break;
      case 'D':
        D(1);
        break;
      case 'R':
        R(1);
        break;
      case 'L':
        L(1);
        break;
      case 'F':
        F(1);
        break;
      case 'B':
        B(1);
        break;
      default:
        validMove = false;
        break;
    }
  }

}


void Cube::output() {
    const char* colorBg[] = {
        "\033[48;2;255;255;255m", // White
        "\033[48;2;255;255;0m",   // Yellow
        "\033[48;2;139;0;0m",     // Dark Red
        "\033[48;2;0;128;0m",     // Green
        "\033[48;2;255;165;0m",   // Orange
        "\033[48;2;0;0;255m"      // Blue
    };
    const char* reset = "\033[0m";

    auto drawBoxRow = [&](int row, int face) {
        for (int col = 0; col < 3; ++col) cout << "+----+  ";
        cout << "\n";
        for (int col = 0; col < 3; ++col) {
            int color = cubes[row * 3 + col][face];
            cout << "| " << colorBg[color] << "  " << reset << " |  ";
        }
        cout << "\n";
        for (int col = 0; col < 3; ++col) std::cout << "+----+  ";
        cout << "\n";
    };

    auto drawFace = [&](int face, const std::string& label = "") {
        if (!label.empty()) std::cout << "       [" << label << "]\n";
        for (int row = 0; row < 3; ++row) {
            std::cout << "      ";
            drawBoxRow(row, face);
        }
        cout << "\n";
    };

    // UP face
    drawFace(0, "UP - White");

    // Side faces: LEFT, FRONT, RIGHT, BACK
    std::cout << "[LEFT - BLUE]       [FRONT - RED]       [RIGHT - ORANGE]       [BACK - GREEN]\n";
    for (int row = 0; row < 3; ++row) {
        for (int face : {5, 2, 4, 3}) {
            for (int col = 0; col < 3; ++col) std::cout << "+----+  ";
            cout << "   ";
        }
        cout << "\n";
        for (int face : {5, 2, 4, 3}) {
            for (int col = 0; col < 3; ++col) {
                int color = cubes[row * 3 + col][face];
                std::cout << "| " << colorBg[color] << "  " << reset << " |  ";
            }
            cout << "   ";
        }
        cout << "\n";
        for (int face : {5, 2, 4, 3}) {
            for (int col = 0; col < 3; ++col) std::cout << "+----+  ";
            cout << "   ";
        }
        cout << "\n";
    }

    // DOWN face
    drawFace(1, "DOWN - Yellow");

    cout << endl;
}



void Cube::scramble() {
  //generate random string and call moves()

}

void Cube::R(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {
    for (int x=0; x<n; ++x) {

      //Orange->White
      newcubes[2][0] = Cube::cubes[6][4];
      newcubes[5][0] = Cube::cubes[3][4];
      newcubes[8][0] = Cube::cubes[0][4];

      //White->Red
      newcubes[2][2] = Cube::cubes[2][0];
      newcubes[5][2] = Cube::cubes[5][0];
      newcubes[8][2] = Cube::cubes[8][0];

      //Red->Yellow
      newcubes[2][1] = Cube::cubes[2][2];
      newcubes[5][1] = Cube::cubes[5][2];
      newcubes[8][1] = Cube::cubes[8][2];

      //Yellow->Orange
      newcubes[6][4] = Cube::cubes[2][1];
      newcubes[3][4] = Cube::cubes[5][1];
      newcubes[0][4] = Cube::cubes[8][1];

      //Rotate Green
      newcubes[0][3] = Cube::cubes[6][3];
      newcubes[1][3] = Cube::cubes[3][3];
      newcubes[2][3] = Cube::cubes[0][3];
      newcubes[3][3] = Cube::cubes[7][3];
      newcubes[5][3] = Cube::cubes[1][3];
      newcubes[6][3] = Cube::cubes[8][3];
      newcubes[7][3] = Cube::cubes[5][3];
      newcubes[8][3] = Cube::cubes[2][3];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
    
    }
  }



}

void Cube::L(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //White->Orange
      newcubes[2][4] = Cube::cubes[6][0];
      newcubes[5][4] = Cube::cubes[3][0];
      newcubes[8][4] = Cube::cubes[0][0];

      //Orange->Yellow
      newcubes[6][1] = Cube::cubes[2][4];
      newcubes[3][1] = Cube::cubes[5][4];
      newcubes[0][1] = Cube::cubes[8][4];

      //Yellow->Red
      newcubes[0][2] = Cube::cubes[0][1];
      newcubes[3][2] = Cube::cubes[3][1];
      newcubes[6][2] = Cube::cubes[6][1];

      //Red->White
      newcubes[0][0] = Cube::cubes[0][2];
      newcubes[3][0] = Cube::cubes[3][2];
      newcubes[6][0] = Cube::cubes[6][2];

      //Rotate Blue
      newcubes[0][5] = Cube::cubes[6][5];
      newcubes[1][5] = Cube::cubes[3][5];
      newcubes[2][5] = Cube::cubes[0][5];
      newcubes[3][5] = Cube::cubes[7][5];
      newcubes[5][5] = Cube::cubes[1][5];
      newcubes[6][5] = Cube::cubes[8][5];
      newcubes[7][5] = Cube::cubes[5][5];
      newcubes[8][5] = Cube::cubes[2][5];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
    }
  }


}

void Cube::U(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Orange->Green
      newcubes[0][3] = Cube::cubes[0][4];
      newcubes[1][3] = Cube::cubes[1][4];
      newcubes[2][3] = Cube::cubes[2][4];

      //Green->Red
      newcubes[0][2] = Cube::cubes[0][3];
      newcubes[1][2] = Cube::cubes[1][3];
      newcubes[2][2] = Cube::cubes[2][3];

      //Red->Blue
      newcubes[0][5] = Cube::cubes[0][2];
      newcubes[1][5] = Cube::cubes[1][2];
      newcubes[2][5] = Cube::cubes[2][2];

      //Blue->Orange
      newcubes[0][4] = Cube::cubes[0][5];
      newcubes[1][4] = Cube::cubes[1][5];
      newcubes[2][4] = Cube::cubes[2][5];

      //Rotate Yellow
      newcubes[0][1] = Cube::cubes[6][1];
      newcubes[1][1] = Cube::cubes[3][1];
      newcubes[2][1] = Cube::cubes[0][1];
      newcubes[3][1] = Cube::cubes[7][1];
      newcubes[5][1] = Cube::cubes[1][1];
      newcubes[6][1] = Cube::cubes[8][1];
      newcubes[7][1] = Cube::cubes[5][1];
      newcubes[8][1] = Cube::cubes[2][1];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
        
    }
  }

}

void Cube::D(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Orange->Blue
      newcubes[6][5] = Cube::cubes[6][4];
      newcubes[7][5] = Cube::cubes[7][4];
      newcubes[8][5] = Cube::cubes[8][4];

      //Blue->Red
      newcubes[6][2] = Cube::cubes[6][5];
      newcubes[7][2] = Cube::cubes[7][5];
      newcubes[8][2] = Cube::cubes[8][5];

      //Red->Green
      newcubes[6][3] = Cube::cubes[6][2];
      newcubes[7][3] = Cube::cubes[7][2];
      newcubes[8][3] = Cube::cubes[8][2];

      //Green->Orange
      newcubes[6][4] = Cube::cubes[6][3];
      newcubes[7][4] = Cube::cubes[7][3];
      newcubes[8][4] = Cube::cubes[8][3];

      //Rotate White
      newcubes[0][0] = Cube::cubes[6][0];
      newcubes[1][0] = Cube::cubes[3][0];
      newcubes[2][0] = Cube::cubes[0][0];
      newcubes[3][0] = Cube::cubes[7][0];
      newcubes[5][0] = Cube::cubes[1][0];
      newcubes[6][0] = Cube::cubes[8][0];
      newcubes[7][0] = Cube::cubes[5][0];
      newcubes[8][0] = Cube::cubes[2][0];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
        
    }
  }


}

void Cube::F(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Blue->Yellow
      newcubes[8][1] = Cube::cubes[2][5];
      newcubes[7][1] = Cube::cubes[5][5];
      newcubes[6][1] = Cube::cubes[8][5];

      //Yellow->Green
      newcubes[0][3] = Cube::cubes[6][1];
      newcubes[3][3] = Cube::cubes[7][1];
      newcubes[6][3] = Cube::cubes[8][1];

      //Green->White
      newcubes[2][0] = Cube::cubes[0][3];
      newcubes[1][0] = Cube::cubes[3][3];
      newcubes[0][0] = Cube::cubes[6][3];

      //White->Blue
      newcubes[2][5] = Cube::cubes[0][0];
      newcubes[5][5] = Cube::cubes[1][0];
      newcubes[8][5] = Cube::cubes[2][0];

      //Rotate Red
      newcubes[0][2] = Cube::cubes[6][2];
      newcubes[1][2] = Cube::cubes[3][2];
      newcubes[2][2] = Cube::cubes[0][2];
      newcubes[3][2] = Cube::cubes[7][2];
      newcubes[5][2] = Cube::cubes[1][2];
      newcubes[6][2] = Cube::cubes[8][2];
      newcubes[7][2] = Cube::cubes[5][2];
      newcubes[8][2] = Cube::cubes[2][2];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
    }
  }


}

void Cube::B(int n) {

  int newcubes[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newcubes[i][j] = Cube::cubes[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Yellow->Blue
      newcubes[6][5] = Cube::cubes[0][1];
      newcubes[3][5] = Cube::cubes[1][1];
      newcubes[0][5] = Cube::cubes[2][1];

      //Blue->White
      newcubes[6][0] = Cube::cubes[0][5];
      newcubes[7][0] = Cube::cubes[3][5];
      newcubes[8][0] = Cube::cubes[6][5];

      //White->Green
      newcubes[8][3] = Cube::cubes[6][0];
      newcubes[5][3] = Cube::cubes[7][0];
      newcubes[2][3] = Cube::cubes[8][0];

      //Green->Yellow
      newcubes[0][1] = Cube::cubes[2][3];
      newcubes[1][1] = Cube::cubes[5][3];
      newcubes[2][1] = Cube::cubes[8][3];

      //Rotate Orange
      newcubes[0][4] = Cube::cubes[6][4];
      newcubes[1][4] = Cube::cubes[3][4];
      newcubes[2][4] = Cube::cubes[0][4];
      newcubes[3][4] = Cube::cubes[7][4];
      newcubes[5][4] = Cube::cubes[1][4];
      newcubes[6][4] = Cube::cubes[8][4];
      newcubes[7][4] = Cube::cubes[5][4];
      newcubes[8][4] = Cube::cubes[2][4];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          Cube::cubes[i][j] = newcubes[i][j];
        }
      }
        
    }
  }


}
