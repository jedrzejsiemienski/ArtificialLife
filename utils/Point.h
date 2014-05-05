/*
 * Point.h
 *
 *  Created on: 29 gru 2013
 *      Author: jedrek
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point();
	Point(float, float);
	virtual ~Point();

	float x;
	float y;
};

#endif /* POINT_H_ */
