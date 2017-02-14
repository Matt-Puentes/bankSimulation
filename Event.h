#ifndef EVENT_H_
#define EVENT_H_

#include"tellerLine.h"
#include<vector>
#include<iostream>
#include<cstdlib>
#include<queue>
class tellerLine;
class Event {
public:
	static int numberOfTellers;
	static bool commonLine;
	static std::priority_queue<Event> *timeLine;
	static int averageServiceTime;
	static int custServed;
	static std::vector<float> timeInBank;
	static std::vector<float> tellerServ;
	static std::vector<float> tellerIdle;
	static float timeWaitBank;
	static float maxSimTime;
	float cEnterTime;
	enum customerState{notC, arriving, in_line, being_served, gathering_stats};
	customerState cState;
	enum tellerState{notT, initial_idle, idle, serving_customer};
	tellerState tState;
	int tellerNumber;
	float time;
	float tellerLastTime;
	char eventType;
	Event(float, char, bool);
	~Event();
	void action(std::vector<tellerLine> *lines);
	void coustomerAction(std::vector<tellerLine> *lines);
	void addSelfToLine(std::vector<tellerLine> *lines);
	void tellerAction(std::vector<tellerLine> *lines);
	Event *getCustomerFromLine(std::vector<tellerLine> *lines);
	void setTellerNumber(int num);
	void setCState(customerState cs);
	void setTState(tellerState ts);
	friend bool operator<(const Event &a, const Event &b) {
		return a.time > b.time;
	}
};

#endif
