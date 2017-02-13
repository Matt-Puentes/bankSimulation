#include"Event.h"
int Event::numberOfTellers = 0;

void Event::coustomerAction(tellerLine *lines){
	if(commonLine){
		lines->add(this);
	}else{

	}
}

void Event::tellerAction(tellerLine *lines){

}

void Event::action(tellerLine *lines) {
	if (eventType == 'c') {
		Event::coustomerAction(lines);
	} else if (eventType == 't') {
		Event::tellerAction(lines);
	}
}

Event::Event(int time, char eventType, bool commonLine) {
	this->time = time;
	this->eventType = eventType;
	this->commonLine = commonLine;
	if (eventType == 't') {
		numberOfTellers++;
		tellerNumber = numberOfTellers;
	} else {
		tellerNumber = -1;
	}
}
Event::~Event() {
	/*
	 if(time)
	 delete(&time);
	 if(eventType)
	 delete(&eventType);
	 */
}

