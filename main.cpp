#include <iostream>

#include "Grammar.h"

int main()
{
	Grammar grammar("test1.txt");
	auto first = grammar.getFirst();
	for (auto it = first.begin(); it != first.end(); it++)
	{
		std::cout << "FIRST(" << it->first << ") = {";
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (it1 != it->second.begin())
				std::cout << ", ";
			std::cout << *it1;
		}
		std::cout << "}" << std::endl;
	}
	return 0;
}