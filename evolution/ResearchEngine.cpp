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
	startPopulationSize = 100;
	f = 0.8f;
	cr = 0.5f;
	movementSteps = 300;
	epochs = 100;
}

ResearchEngine::~ResearchEngine() {
	delete start;
	delete end;
}

void ResearchEngine::doPlannedResearches(bool showResults){
	Environment env(*start, *end, type, startPopulationSize, f, cr, movementSteps);
	env.epochs(epochs);

	Worm * worm = env.getBestWorm();
	worm->saveToFile(createFileName("", "_worm.txt"));

	saveResultsToFile(createFileName("", "_results.txt"), env.getResults());

	if(showResults){
		SDLInterface inteface;
		inteface.displayWorm(worm, movementSteps, end, 50);
	}

	env.clear();
}

void ResearchEngine::saveResultsToFile(string name, vector<float> results){
	ofstream file;

	file.open(name.c_str());

	file << start->x << " " << start->y << endl ;
	file << end->x << " " << end->y << endl ;
	file << type << endl ;
	file << startPopulationSize << endl ;
	file << f << endl ;
	file << cr << endl ;
	file << movementSteps << endl ;
	file << epochs << endl ;
	file << endl ;

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
	ss << start->x << "_" << start->y << "_";
	ss << end->x   << "_" << end->y   << "_";
	ss << type << "_";
	ss << startPopulationSize << "_";
	ss << f << "_";
	ss << cr << "_";
	ss << movementSteps << "_";
	ss << epochs << "_";

	results += ss.str();
	results += postfix;
	return results;
}

