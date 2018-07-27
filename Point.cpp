#include "Point.h"

void Point::rotateRight90Point(float cx, float cy)
{
	float angle = (float)((M_PI / 2));
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	this->setX((int)(this->getX() - cx));
	this->setY((int)(this->getY() - cy));

	// rotate point
	float xnew = this->getX() * c - this->getY() * s;
	float ynew = this->getX() * s + this->getY() * c;

	// translate point back:
	this->setX((int)(xnew + cx));
	this->setY((int)(ynew + cy));
}