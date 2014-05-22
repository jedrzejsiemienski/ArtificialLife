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
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_gfxPrimitives.h"

using namespace std;

class ResearchEngine {
public:
	ResearchEngine();
	virtual ~ResearchEngine();
	void doPlannedResearches(bool showResults = true);

private:
	void doSingleResearch(Point*, Point*, int, int, float, float, int, bool showResult = false);

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

	SDL_Surface* screen;
	int screenWidth;
	int screenHeight;
	void initScreen();
	void showProgressBar(float, float);
	void killScreen();
};

#endif /* RESEARCH_ENGINE_H_ */

