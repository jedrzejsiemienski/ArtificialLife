/*
 * ResearchEngine.h
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#ifndef RESEARCH_ENGINE_H_
#define RESEARCH_ENGINE_H_

#include <fstream>
#include <iterator>
#include <string>

#include "../evolution/Environment.h"
#include "../interface/SDLInterface.h"

using namespace std;

class ResearchEngine {
public:
	ResearchEngine();
	virtual ~ResearchEngine();
	void doPlannedResearches(bool showResults = true);

private:
	void saveResultsToFile(string, vector<float>);

	string createFileName(string, string);

	Point * start;
	Point * end;
	int type;
	int startPopulationSize;
	float f;
	float cr;
	int movementSteps;
	int epochs;
};

#endif /* RESEARCH_ENGINE_H_ */
