#pragma once

#include "Point.h"

#include "TetrisGame.h"
#include "GameBoard.h"

#define  NUM_OF_ROTATIONS 4
#define EXPLOSION_RADIUS 1
class Shape {
public:
	enum ARROWS { LEFT = 'a', CHANGER = 32 , RIGHT = 'd', DOWN = 'x', JOKERSTOP = 's', IMMIDIATE_DOWN = 'z' };
	enum ShapeMaxLen { MAXLEN = 4 }; 
	enum ShapeDir { ORIGINAL, CW90, CW180, CW270 }; //CW= clockwise 
	enum ShapeType { SQUARE, LINE, TSHAPE, JOKER, BOMB , ZSHAPE, LSHAPE};
	enum Material { MATERIAL = '*' , BOMB_MATERIAL = '@'};
	Shape() {}
	virtual	void draw() = 0;
	virtual	bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) = 0;
	virtual	void rotateRight(GameBoard & gameBoard, Menu& menu) {}
	virtual	void Shape::immidiateDown(GameBoard &gameBoard, Menu& menu) = 0;
	virtual inline void getBodyCellXY(int index, int &x, int &y) const = 0;
	virtual int getLen() const = 0;
	virtual Shape::ShapeDir getShapeDir() const;
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const {}
	virtual Shape::ShapeType  getShapeType() const = 0;
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu)  = 0;
	virtual int cleanRows(GameBoard &gameBoard,  Menu &menu) const;
	virtual bool isGameOver() const = 0;
	virtual int explodeBomb(GameBoard &gameBoard) {
		return 0;
	}
	virtual bool improveShapeStopReactionTime(bool &getChar, char &keyPressed, GameBoard &gameBoard, Menu &menu, int &bodyX, int & bodyY) const { getChar = true; return false; }
	virtual int getStartY() const = 0;
	~Shape() { }
	inline char getChar() const{return c;}
private:
	ShapeDir shapeDir;
	ShapeType shapeType;
	char c = MATERIAL;

};

