#include "list.h"
#include <iostream>

int main(int argc, char **argv){

	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_front(5);
	l.push_front(6);
	std::cout << "--------------------------\n";
	l.show();


	return 0;
}

