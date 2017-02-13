#ifndef EVENT_H_
#define EVENT_H_
#include"tellerLine.h"
class tellerLine;
class Event {
public:
	static int numberOfTellers;
	int tellerNumber;
	float time;
	char eventType;
	bool commonLine;
	Event(int, char, bool);
	~Event();
	void action(tellerLine *lines);
	void coustomerAction(tellerLine *lines);
	void tellerAction(tellerLine *lines);
	friend bool operator<(const Event &a, const Event &b) {
		return a.time > b.time;
	}
};

#endif
