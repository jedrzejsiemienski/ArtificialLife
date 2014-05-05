/*
 * KonwerterDanych.h
 *
 *  Created on: 3 lis 2013
 *      Author: jedrek
 */

#ifndef KONWERTERDANYCH_H_
#define KONWERTERDANYCH_H_


class KonwerterDanych {
public:
	KonwerterDanych(int, int);
	~KonwerterDanych();
	int getBucketsNumber();
	int getInputRange();
	int * convert(int);

private:
	int bucketsNumber;
	int inputRange;
	int bucketWidth;
};

#endif /* KONWERTERDANYCH_H_ */
