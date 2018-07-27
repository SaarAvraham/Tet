#pragma once
#include "shape.h"

#define SQUARE_SIZE 4
class Square : public Shape
{
private:
	ShapeDir shapeDir;
	Point body[SQUARE_SIZE];
	char c = MATERIAL;

public:
	 virtual inline int getLen() const override{return SQUARE_SIZE;}
	inline void getBodyCellXY(int index, int &x, int &y) const override
	{
		x = body[index].getX();
		y = body[index].getY();
	}
	Square(char material);
	virtual void draw() override;
	virtual bool move(ARROWS key, GameBoard& gameBoard, Menu& menu) override;
	virtual void immidiateDown(GameBoard &gameBoard, Menu& menu) override;
	virtual void updateBoard(char keyPressed, GameBoard & gameBoard, Menu& menu, Point lastPos[Shape::MAXLEN] = NULL) const override;
	virtual Shape::ShapeType getShapeType() const override { return Shape::SQUARE; }
	virtual int getStartY() const override { return STARTY; }
	virtual bool hasReachedBottom(GameBoard &gameBoard, Menu& menu)  override;
	virtual bool isGameOver() const override;
	~Square() {}

};