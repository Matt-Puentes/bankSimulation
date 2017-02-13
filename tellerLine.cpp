#include"tellerLine.h"
#include<iostream>
lineNode::lineNode(Event *event) {
	this->event = event;
	this->next = 0;
}
lineNode::~lineNode() {

}
tellerLine::tellerLine() {
	this->head = 0;
}
tellerLine::~tellerLine() {
}
void tellerLine::add(Event *event) {
	if (head == 0)
		head = new lineNode(event);
	else {
		lineNode *cursor = head;
		while (cursor->next != 0) {
			cursor = cursor->next;
		}
		cursor->next = new lineNode(event);
	}
}

Event *tellerLine::pop() {
	if (head == 0)
		return 0;
	lineNode* temp = head;
	head = temp->next;
	return temp->event;
}

void tellerLine::printQueue() {
	if (head == 0) {
		return;
	}
	lineNode *cursor = head;

	while (cursor != 0) {
		std::cout << cursor->event->time << std::endl;
		cursor = cursor->next;
	}
}
