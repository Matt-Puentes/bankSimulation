//Matthew Puentes Andrew Levy
#include<iostream>
#include<queue>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include"tellerLine.h"
#include"Event.h"

float avgVector(std::vector<float> s){
	float av = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		av += s.at(i);
	}
	return av/s.size();
}


int main(int argc, char* argv[]) {
	if (argc == 6) {
		unsigned int i = atoi(argv[5]);
		srand(i);
	} else if (argc == 5)
		srand(time(0));
	else {
		std::cout << "Please input 4 or 5 arguments" << std::endl;
	}
	int custNum = atoi(argv[1]);
	int tellNum = atoi(argv[2]);
	float simTime = atoi(argv[3])*60;
	Event::maxSimTime = simTime;
	float avgServiceTime = atoi(argv[4])*60;


	std::cout <<std::endl << "first trial with one line per teller" <<std::endl;
	Event::commonLine = false;
	std::priority_queue<Event> timeLine;
	Event::timeLine = &timeLine;
	Event::averageServiceTime = avgServiceTime;
	Event::timeInBank = *(new std::vector<float>());
	Event::timeWaitBank = 0;

	//create Customers
	for (int i = 0; i < custNum; i++) {
		float randTime = (rand() / float(RAND_MAX)) * (simTime);
		const Event newC = *(new Event(randTime, 'c', true));
		timeLine.push(newC);
	}

	//create tellers, tellerLines.
	std::vector<tellerLine> *tellerLineList = new std::vector<tellerLine>();
	for (int i = 0; i < tellNum; i++) {
		tellerLineList->push_back(*(new const tellerLine()));
		timeLine.push(*(new Event(0, 't', false)));
	}

	float totalTime = 0;
	float time = 0;
	while (!timeLine.empty()) {
		Event e = timeLine.top();
		time = e.time;
		timeLine.pop();
		e.action(tellerLineList);

	}
	float avServeTime = avgVector(Event::timeInBank);
	float avTellerServe = avgVector(Event::tellerServ);
	float avTellerIdle = avgVector(Event::tellerIdle);
	totalTime = time;
	std::cout << "there were " << custNum << " customers helped in " << float(totalTime/60) << " minutes" <<std::endl;
	std::cout << "on average, customers spend " << float(avServeTime/60) << " min in the bank" << std::endl;
	std::cout << "The longest wait time a customer had was " << float(Event::timeWaitBank/60) << std::endl;
	std::cout << "On average the tellers idled for " << float(avTellerIdle) << " minutes and served coustomers for "
			<< float(avTellerServe) << " minutes " << std::endl;



	std::cout <<std::endl << "second trial with one common line" <<std::endl;

	//time with one common line.
	Event::commonLine = true;
	timeLine = *(new std::priority_queue<Event>());
	Event::timeLine = &timeLine;
	Event::averageServiceTime = avgServiceTime;
	Event::timeInBank = *(new std::vector<float>());
	Event::timeWaitBank = 0;

	//create Customers
	for (int i = 0; i < custNum; i++) {
		float randTime = (rand() / float(RAND_MAX)) * (simTime);
		const Event newC = *(new Event(randTime, 'c', true));
		timeLine.push(newC);
	}

	//create tellers, tellerLines.
	tellerLineList = new std::vector<tellerLine>();
	for (int i = 0; i < tellNum; i++) {
		tellerLineList->push_back(*(new const tellerLine()));
		timeLine.push(*(new Event(0, 't', false)));
	}

	totalTime = 0;
	time = 0;
	while (!timeLine.empty()) {
		Event e = timeLine.top();
		time = e.time;
		timeLine.pop();
		e.action(tellerLineList);

	}
	avServeTime = avgVector(Event::timeInBank);
	avTellerServe = avgVector(Event::tellerServ);
	avTellerIdle = avgVector(Event::tellerIdle);
	totalTime = time;
	std::cout << "there were " << custNum << " customers helped in " << float(totalTime/60) << " minutes" <<std::endl;
	std::cout << "on average, customers spend " << float(avServeTime/60) << " min in the bank" << std::endl;
	std::cout << "The longest wait time a customer had was " << float(Event::timeWaitBank/60) << std::endl;
	std::cout << "On average the tellers idled for " << float(avTellerIdle) << " minutes and served coustomers for "
			<< float(avTellerServe) << " minutes " << std::endl;


	return 1;
}

