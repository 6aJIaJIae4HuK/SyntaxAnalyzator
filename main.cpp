#include <iostream>

#include "Analyser.h"
#include "Grammar.h"

int main()
{
	freopen("log.txt", "w", stdout);
	Analyser analyser("CodeGrammar.txt");
	const Grammar& grammar = analyser.getGrammar();
	auto first = grammar.getFirst();
	for (auto it = first.begin(); it != first.end(); it++)
	{
		std::cout << "FIRST('" << it->first << "') = {";
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (it1 != it->second.begin())
				std::cout << ", ";
			std::cout << '\'' << *it1 << '\'';
		}
		std::cout << "}" << std::endl;
	}

	std::cout << std::endl;

	auto follow = grammar.getFollow();
	for (auto it = follow.begin(); it != follow.end(); it++)
	{
		std::cout << "FOLLOW('" << it->first << "') = {";
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (it1 != it->second.begin())
				std::cout << ", ";
			std::cout << '\'' << *it1 << '\'';
		}
		std::cout << "}" << std::endl;
	}

	std::cout << std::endl;

	analyser.parseFromFile("code.txt");

	std::cout << std::endl << "Count of errors: " << analyser.getErrorCount() << std::endl;

	return 0;
}