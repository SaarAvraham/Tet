

#include <conio.h>
#include "shape.h"
#include "GameBoard.h"
#include <cwchar>
#include <MMSystem.h>
#include <mciapi.h>
#include "Menu.h"

#pragma comment(lib, "winmm.lib")

#ifndef _TETRISGAME_H_
#define _TETRISGAME_H_


#include "shape.h"
#include "Menu.h"

#define FIRST_ROW_GAME 3
#define LAST_ROW_GAME 17

#define NUM_OF_TYPES 5

#define NUM_OF_RANDS 2

#define RAND_RANGE 17
#define LINE_RANGE_RAND_START 0
#define LINE_RANGE_RAND_END 2
#define SQUARE_RANGE_RAND_START 3
#define SQUARE_RANGE_RAND_END 5
#define TSHAPE_RANGE_RAND_START 6
#define TSHAPE_RANGE_RAND_END 8
#define LSHAPE_RANGE_RAND_START 9
#define LSHAPE_RANGE_RAND_END 11
#define	ZSHAPE_RANGE_RAND_START 12
#define	ZSHAPE_RANGE_RAND_END 14
#define	JOKER_RANGE_RAND_START 15


#define SCORE_PENALTY -50
#define ROW_SCORE 100
#define JOKER_ROW_SCORE 50
#define ROW_MULTI_BONUS 200

#define FIRST_COL_GAME 2
#define LAST_COL_GAME 11

#define ESC 27


class Menu;
class GameBoard;
class TetrisGame
{
public:
	void run();
	bool MenuKeysManager(Menu *menu, char keyPressed, bool &stopGame, bool& clear, bool& pause);
};
#endif