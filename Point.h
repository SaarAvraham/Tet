#pragma once

#include <iostream>
#include "Gotoxy.h"
using namespace std;
# define M_PI           3.14159265358979323846  
enum StartPoint { STARTX = 6, STARTY = 3 }; 


class Point
{
	int x;
	int y;
public:
	Point(int x = STARTX, int y = STARTY) {
		this->x = x;
		this->y = y;
	}
	void rotateRight90Point(float cx, float cy);
	inline Point right() const {return Point(x + 1, y);}
	inline Point down() const {return Point(x, y + 1);}
	inline Point left() const {return Point(x-1, y);}
	inline Point up() const {return Point(x, y-1);}
	inline void draw(char c = '*') const {
		gotoxy(x, y);
		cout << c;
		cout.flush();
	}

	inline int getX()  const{return x;}
	inline int getY() const{return y;}
	inline void setX(int x){this->x = x;}
	inline void setY(int y){this->y = y;}


};
