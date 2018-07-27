#pragma once
#include "shape.h"

#define BOMB_LEN 1
class Bomb : public Shape
{
private:
	Point body[BOMB_LEN];
	char material = BOMB_MATERIAL;
public:
	virtual inline int getLen() const override{return BOMB_LEN;}
	virtual inline void getBodyCellXY(int index, int &x,int &y) const override
	{
		x = body[0].getX();
		y = body[0].getY();
	}
	Bomb(char material);
	virtual void draw() override ;
	virtual bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual Shape::ShapeType getShapeType() const override  { return Shape::BOMB; }
	int explodeBomb(GameBoard &gameBoard);
	virtual int getStartY() const override { return STARTY; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu) override;
	virtual int cleanRows(GameBoard &gameBoard, Menu &menu) const override { return 0; }
	virtual inline bool isGameOver() const override { return false; }
	~Bomb() {};
};
