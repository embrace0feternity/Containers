#include "list.h"
#include <iostream>

int main(int argc, char **argv){

	list<int> l2 = { 1, 6, 9, 21, -6 };
	list<int> l3(5);
	std::copy(l2.begin(), l2.end(), l3.begin());

	for (const auto &i : l3)
		std::cout << i << ' ';
	std::cout << std::endl;
	l3.push_back(2);
	l3.push_front(-2);
	for (const auto &i : l3)
			std::cout << i << ' ';
		std::cout << std::endl;

	l3.push_back(3);
	l3.push_front(-3);

	l3.push_back(4);
	l3.push_front(-4);
	for (const auto &i : l3)
			std::cout << i << ' ';
		std::cout << std::endl;
	return 0;
}

