#pragma once
#include "shape.h"
#include "GlobalFunctions.h"
#define JOKER_LEN 1
class Joker :public Shape
{
private:

	Point body[JOKER_LEN];
	char material = MATERIAL;

public:
	virtual inline int getLen() const override{return JOKER_LEN;}
	virtual inline void getBodyCellXY(int index, int &x, int &y) const override
	{
		x = body[0].getX();
		y = body[0].getY();
	}
	Joker(char material);
	virtual void draw() override;
	virtual bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual Shape::ShapeType getShapeType() const override { return Shape::JOKER; }
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const override;
	virtual int getStartY() const override { return STARTY; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu) override;
	virtual int cleanRows(GameBoard &gameBoard, Menu &menu) const override;
	virtual inline bool isGameOver() const override { return false; }
	virtual bool improveShapeStopReactionTime(bool &getChar, char &keyPressed, GameBoard &gameBoard, Menu &menu, int &bodyX, int & bodyY) const override;
	~Joker() { }

};