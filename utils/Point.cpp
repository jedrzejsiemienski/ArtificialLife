/*
 * Point.cpp
 *
 *  Created on: 29 gru 2013
 *      Author: jedrek
 */

#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
Point operator+(Point* left, Point * right) {
	float x = left->x + right->x;
	float y = left->y + right->y;
	return Point(x, y);
}
*/

Point::~Point() {}
