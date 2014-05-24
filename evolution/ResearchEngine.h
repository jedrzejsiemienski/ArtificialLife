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
	void _doPlannedResearches(bool showResults);

	bool isRunning();
	int getCurrentEpoch();
	int getEpochs();
	int getCurrentResearch();
	int getResearches();

private:
	Point * start;
	Point * end;
	int type;
	int startPopulationSize;
	vector<float> f;
	vector<float> cr;
	int movementSteps;

	bool running;
	int currentEpoch;
	int epochs;
	int currentResearch;
	int researches;

	void doSingleResearch(Point*, Point*, int, int, float, float, int, bool showResult = false);
	void saveResultsToFile(string, vector<float>);
	string createFileName(string, string, float, float);
};

int _researchThread(void *data);
int _progressThread(void *data);

#endif /* RESEARCH_ENGINE_H_ */


