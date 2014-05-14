/*
 * Genotype.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "Genotype.h"

Genotype::Genotype(float f, float cr) {
	this->f = f;
	this->cr = cr;
}

Genotype::~Genotype() {
}

//substract given genotype from current genotype
Genotype* Genotype::substract(Genotype* x){
	return x;
}

//add given genotype to current genotype
Genotype* Genotype::add(Genotype* x){
	return x;
}

//mutliplies everything from genotype by given number
Genotype* Genotype::multiply(float a){
	return this;
}

//pobiera mutanta v, mutuje go ze soba i zwraca u - osobnika probnego
Genotype* Genotype::crossWith(Genotype* x){
	return this;
}

//mutates current with 2 given
Genotype* Genotype::mutateWith(Genotype* x1, Genotype* x2){
	return this->add((x1->substract(x2))->multiply(f));
}
