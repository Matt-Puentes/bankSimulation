#include"tellerLine.h"
#include<iostream>
lineNode::lineNode(Event *event) {
	this->event = event;
	this->next = 0;
}
lineNode::~lineNode() {

}
tellerLine::tellerLine() {
	length = 0;
	this->head = 0;
}
tellerLine::~tellerLine() {
}
void tellerLine::add(Event *event) {
	length++;
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
	length--;
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
