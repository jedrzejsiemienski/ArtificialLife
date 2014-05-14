/*
 * Genotype.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef GENOTYPE_H_
#define GENOTYPE_H_

class Genotype {
public:
	Genotype(float, float);
	virtual ~Genotype();

	Genotype* substract(Genotype*);  //substract given genotype from current genotype
	Genotype* add(Genotype*);  //add given genotype to current genotype
	Genotype* multiply(float); //mutliplies everything from genotype by given number
	Genotype* crossWith(Genotype*); //pobiera mutanta v, mutuje go ze soba i zwraca u - osobnika probnego
	Genotype* mutateWith(Genotype*, Genotype*); //mutates current with 2 given

private:
	float f;
	float cr;
};

#endif /* GENOTYPE_H_ */
