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

struct Route {
	Point* start;
	Point* end;
};

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
	vector<int> epochsVector;
	vector<int> types;
	vector<Route*> routes;
	vector<int> startPopulationSizes;
	vector<float> f;
	vector<float> cr;
	int movementSteps;

	bool running;
	int currentEpoch;
	int currentResearch;
	int epochsTotal;
	int researchesTotal;

	void doSingleResearch(Point*, Point*, int, int, float, float, int, int, bool showResult = false);
	void saveResultsToFile(string, vector<float>);
	string createFileName(string, string, Point*, Point*, int, int, float, float, int, int);
};

int _researchThread(void *data);
int _progressThread(void *data);

#endif /* RESEARCH_ENGINE_H_ */


