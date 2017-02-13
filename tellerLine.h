#ifndef TELLERLINE_CPP_
#define TELLERLINE_CPP_
#include"Event.h"
class Event;
class lineNode {
public:
	Event *event;
	lineNode *next;
	lineNode(Event *event);
	~lineNode();
};
class tellerLine {
public:
	lineNode *head;
	tellerLine();
	~tellerLine();
	void add(Event *event);
	Event *pop();
	void printQueue();
};
#endif
