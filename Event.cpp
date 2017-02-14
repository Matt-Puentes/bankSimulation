#include"Event.h"
int Event::numberOfTellers = 0;
bool Event::commonLine = true;
int Event::averageServiceTime = 0;
float Event::maxSimTime = 0;
std::priority_queue<Event> *Event::timeLine = 0;
std::vector<float> Event::timeInBank = *(new std::vector<float>);
std::vector<float> Event::tellerServ = *(new std::vector<float>);
std::vector<float> Event::tellerIdle = *(new std::vector<float>);
float tellerLastTime = 0;


float Event::timeWaitBank = 0;
int Event::custServed = 0;

void Event::addSelfToLine(std::vector<tellerLine> *lines) {
	if (commonLine) {
		lines->at(0).add(this);
	} else {
		int smallestLineSize = -1;
		for (unsigned int i = 0; i < lines->size(); i++) {
			if (lines->at(i).length < smallestLineSize
					|| smallestLineSize == -1) {
				smallestLineSize = lines->at(i).length;
			}
		}
		int numberOfSmallestLines = 0;
		for (unsigned int i = 0; i < lines->size(); i++) {
			if (lines->at(i).length == smallestLineSize)
				numberOfSmallestLines++;
		}

		int chosenLine = (rand() / float(RAND_MAX))
				* float(numberOfSmallestLines) + 1;
		int cursor = 0;
		for (unsigned int i = 0; i < lines->size(); i++) {
			if (lines->at(i).length == smallestLineSize)
				cursor++;
			if (cursor == chosenLine) {
				lines->at(i).add(this);
				break;
			}
		}
	}
}

void Event::coustomerAction(std::vector<tellerLine> *lines) {
	if (cState == arriving) {
		cState = in_line;
		addSelfToLine(lines);
	} else if (cState == being_served) {
		float totalTime = time - cEnterTime;
		timeInBank.push_back(totalTime);
	}
}

Event *Event::getCustomerFromLine(std::vector<tellerLine> *lines) {
	if (commonLine) {
		return lines->at(0).pop();
	} else {
		if (lines->at(tellerNumber - 1).length > 0) {
			return lines->at(tellerNumber - 1).pop();
		} else {
			int nonEmptyLines = 0;
			for (unsigned int i = 0; i < lines->size(); i++) {
				if (lines->at(i).length > 0)
					nonEmptyLines++;
			}
			int chosenLine = (rand() / float(RAND_MAX)) * nonEmptyLines+1;
			int cursor = 0;
			for (unsigned int i = 0; i < lines->size(); i++) {
				if (cursor == chosenLine) {
					return lines->at(i).pop();
				}
				if (lines->at(i).length > 0)
					cursor++;
			}
		}
	}
	return 0;
}

void Event::tellerAction(std::vector<tellerLine> *lines) {
	if (tState == initial_idle) {
		float idleTime = (rand() / float(RAND_MAX)) * 600;
		if (time <= maxSimTime) {
			Event *newE = new Event(time + idleTime, eventType, false);
			newE->setTellerNumber(tellerNumber);
			newE->setTState(serving_customer);
			tellerIdle.push_back(time - tellerLastTime);
			newE->tellerLastTime = time;
			timeLine->push(*newE);
		}
	} else if (tState == idle) {
		float idleTime = (rand() / float(RAND_MAX)) * 150;
		if (time <= maxSimTime) {
			Event *newE = new Event(time + idleTime, eventType, false);
			newE->setTellerNumber(tellerNumber);
			newE->setTState(serving_customer);
			tellerIdle.push_back(time - tellerLastTime);
			newE->tellerLastTime = time;
			timeLine->push(*newE);
		}
	} else if (tState == serving_customer) {
		Event *customer = getCustomerFromLine(lines);
		if (customer != 0) {
			Event::custServed++;
			float helpingCustomerTime = averageServiceTime * 2
					* (rand() / RAND_MAX);
			Event *newCE = new Event(time + helpingCustomerTime, 'c', false);
			newCE->setCState(being_served);
			newCE->cEnterTime = customer->cEnterTime;
			if(time-newCE->cEnterTime > Event::timeWaitBank)
				Event::timeWaitBank= time-newCE->cEnterTime;
			newCE->timeWaitBank = time;
			timeLine->push(*newCE);

			Event *newE = new Event(time + helpingCustomerTime, eventType,
					false);
			newE->setTellerNumber(tellerNumber);
			newE->setTState(serving_customer);
			tellerServ.push_back(time - tellerLastTime);
			newE->tellerLastTime = time;
			timeLine->push(*newE);
		} else {
			Event *newE = new Event(time + 1, eventType, false);
			newE->setTellerNumber(tellerNumber);
			newE->setTState(idle);
			newE->tellerLastTime = time;
			timeLine->push(*newE);
		}

	}

}

void Event::action(std::vector<tellerLine> *lines) {
	if (eventType == 'c') {
		Event::coustomerAction(lines);
	} else if (eventType == 't') {
		Event::tellerAction(lines);

	}

}

void Event::setTellerNumber(int num) {
	this->tellerNumber = num;
}
void Event::setCState(customerState cs) {
	cState = cs;
}
void Event::setTState(tellerState ts) {
	tState = ts;
}

Event::Event(float time, char eventType, bool t) {
	tellerLastTime = 0;
	if (t)
		cEnterTime = time;
	cEnterTime = 0;
	this->time = time;
	this->eventType = eventType;
	if (eventType == 't') {
		cState = notC;
		tState = initial_idle;
		numberOfTellers++;
		tellerNumber = numberOfTellers;
	} else {
		cState = arriving;
		tState = notT;
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

