/*
 * ResearchEngine.cpp
 *
 *  Created on: 22 maj 2014
 *      Author: jedrek
 */

#include "ResearchEngine.h"

ResearchEngine::ResearchEngine() {
	start = new Point(100, 100);
	end = new Point(900, 600);
	type = 2;
	startPopulationSize = 50;
	f = 0.8f;  //0.4f, 0.5f, 0.7f, 0.09f
	cr = 0.5f; //0.1f, 0.5f, 0.9f
	movementSteps = 300;
	epochs = 5;

	screenWidth = 1000;
	screenHeight = 100;
}

ResearchEngine::~ResearchEngine() {
	delete start;
	delete end;
}

void ResearchEngine::doPlannedResearches(bool showResults){
	doSingleResearch(start, end, 1, startPopulationSize, f, cr, movementSteps, true);
}

void ResearchEngine::doSingleResearch(Point *start, Point *end, int type, int populationSize, float f, float cr, int movementSteps, bool showResult){
	Environment env(*start, *end, type, startPopulationSize, f, cr, movementSteps);
	env.epochs(epochs);
	Worm * worm = env.getBestWorm();
	worm->saveToFile(createFileName("", "_worm.txt"));
	saveResultsToFile(createFileName("", "_results.txt"), env.getResults());

	if(showResult){
		SDLInterface inteface;
		inteface.displayWorm(worm);
	}

	env.clear();
}

void ResearchEngine::saveResultsToFile(string name, vector<float> results){
	ofstream file;

	file.open(name.c_str());
/*
	file << type << endl ;
	file << start->x << " " << start->y << endl ;
	file << end->x << " " << end->y << endl ;
	file << f << endl ;
	file << cr << endl ;
	file << startPopulationSize << endl ;
	file << movementSteps << endl ;
	file << epochs << endl ;
	file << endl ;
*/
	vector<float>::iterator iter = results.begin();
	while(iter != results.end()){
		file << *iter << endl;
		iter++;
	}

	file.close();
}

string ResearchEngine::createFileName(string prefix, string postfix){
	string results = "";
	results += prefix;

	stringstream ss;
	ss << type << "_";
	ss << start->x << "_" << start->y << "_";
	ss << end->x   << "_" << end->y   << "_";
	ss << f << "_";
	ss << cr << "_";
	ss << startPopulationSize << "_";
	ss << movementSteps << "_";
	ss << epochs << "_";

	results += ss.str();
	results += postfix;
	return results;
}

void ResearchEngine::initScreen(){
	SDL_Init( SDL_INIT_VIDEO );

	screen = SDL_SetVideoMode( screenWidth, screenHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Reasearch progress", 0 );
}

void ResearchEngine::killScreen(){
	SDL_Quit();
}

void ResearchEngine::showProgressBar(float a, float b){
	int barHeight = 30;
	int offset1 = 5;
	int offset2 = 50;
	int start = 5;
	float barWidth = (float)screenWidth - 5.0f;
	float progressA = barWidth*a;
	float progressB = barWidth*b;

	boxRGBA(screen, 0, 0, screenWidth, screenHeight, 255, 255, 255, 255);
	rectangleRGBA(screen, start, offset1, barWidth, barHeight + offset1, 0, 0, 255, 255);
	boxRGBA(screen, start, offset1, progressA, barHeight + offset1, 0, 0, 255, 255);
	rectangleRGBA(screen, start, offset2, barWidth, barHeight + offset2, 0, 0, 255, 255);
	boxRGBA(screen, start, offset2, progressB, barHeight + offset2, 0, 0, 255, 255);
	SDL_Flip(screen);
}
