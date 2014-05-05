/*
 * KonwerterDanych.cpp
 *
 *  Created on: 3 lis 2013
 *      Author: jedrek
 */

#include "KonwerterDanych.h"
#include <iostream>

using namespace std;

KonwerterDanych::KonwerterDanych(int givenBucketsNumber, int givenInputRange){
	bucketsNumber = givenBucketsNumber;
	inputRange = givenInputRange;
	bucketWidth = inputRange / bucketsNumber;

//	cout << "inputRange : " << inputRange << endl;
//	cout << "bucketsNumber : " << bucketsNumber << endl;
//	cout << "bucketWidth : " << bucketWidth << endl;
}

KonwerterDanych::~KonwerterDanych() {}

int KonwerterDanych::getBucketsNumber() {
	return bucketsNumber;
}


int KonwerterDanych::getInputRange() {
	return inputRange;
}


int * KonwerterDanych::convert(int number) {
	int* x = new int[inputRange];

	for (int i = 0; i < bucketsNumber; i++){
		x[i] = 0;
	}

	int index = number/bucketWidth;
	if(index >= bucketsNumber){
		//cout << "jest" << endl;
		index = bucketsNumber - 1;
	}

	x[index] = 1;
	//cout << "index - " << index << ", x[] = " << x[index] << endl;
	return x;
}


 /* namespace std */
