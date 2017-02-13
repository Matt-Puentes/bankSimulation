#include<iostream>
#include<queue>
#include<vector>
#include"tellerLine.h"
#include"Event.h"
int main(int argc, char* argv[]) {
	if (argc < 4 || argc > 5) {
		std::cout << "Please input 4 or 5 arguments" << std::endl;
	}

	std::priority_queue<Event> timeLine;

	Event *a = new Event(5, 'c', true);
	Event *b = new Event(3, 'c', true);
	Event *c = new Event(1, 'c', true);

	timeLine.push(*b);
	timeLine.push(*c);
	timeLine.push(*a);
	timeLine.push(*(new Event(15, 't', true)));

	while (!timeLine.empty()) {
		Event q = timeLine.top();
		std::cout << q.time << std::endl;
		timeLine.pop();
	}

	std::cout << "=)" << std::endl;

	tellerLine *t = new tellerLine();
	t->add(new Event(1, 'c', true));
	t->add(a);
	t->add(c);
	t->add(b);
	t->printQueue();
	std::cout << "----" << std::endl;
	t->pop();
	t->printQueue();

	std::cout << "program start" << std::endl;
	std::vector<tellerLine> *tellerLineList = new std::vector<tellerLine>();


	return 1;
}
