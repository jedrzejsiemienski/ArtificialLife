/*
 * ChromosomesCrosser.h
 *
 *  Created on: 28 gru 2013
 *      Author: jedrek
 */

#ifndef CHROMOSOMESCROSSER_H_
#define CHROMOSOMESCROSSER_H_

#include "Chromosom.h"
#include <time.h>
#include <stdlib.h>

enum crossingTypes { MULTI_POINT, HOMOGENEOUS};

class ChromosomesCrosser {
public:
	void static mutate(Chromosom *, float, float); //mutacja chromosomu
	Chromosom static * cross(Chromosom *, Chromosom *, crossingTypes, double); //krzyzowanie 2 chromosomow

private:
	float static randomNumber();
	bool static assertEqualStructure(Chromosom *, Chromosom *);
	Chromosom static * multiPointCrossing(Chromosom *, Chromosom *, double);
	Chromosom static * homogeneousCrossing(Chromosom *, Chromosom *, double);
};

#endif /* CHROMOSOMESCROSSER_H_ */
