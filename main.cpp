#include <iostream>
using namespace std;
#include "GameBoard.h"
#include <Windows.h>
#include "Shape.h"
#include "TetrisGame.h"
#include "Line.h"
#include "GameBoard.h"
#include "Joker.h"
#include "Square.h"
#include <cwchar>
#include <MMSystem.h>
#include <mciapi.h>
#include <math.h>
#include "TShape.h"
#include "ZShape.h"
#include "LShape.h"
#pragma comment(lib, "winmm.lib")




int main() {
	TetrisGame game;
	game.run();
	return 0;
}
