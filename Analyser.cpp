#include <fstream>
#include <iostream>

#include "Analyser.h"

Analyser::Analyser(const std::string& grammarFileName) : m_grammar(grammarFileName)
{

}

const Grammar& Analyser::getGrammar() const
{
	return m_grammar;
}

bool Analyser::isAcceptable(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	std::string inputString = "";
	std::string line;
	while (std::getline(inputFile, line))
	{
		inputString += line;
		inputString += ' ';
	}
	inputString.pop_back();
	int pos = 0;

	while ((pos = inputString.find("  ")) != std::string::npos)
	{
		inputString.replace(pos, 2, " ");
		pos++;
	}

	inputString.push_back('$');

	m_stack.clear();
	m_stack.push_back('$');
	m_stack.push_back(m_grammar.getFirstNonTerminal());

	do
	{
		char X = m_stack.back();
		char a = inputString.front();
		auto table = m_grammar.getTable();
		if (m_grammar.getTerminales().find(m_stack.back()) != m_grammar.getTerminales().end())
		{
			if (X == a)
			{
				m_stack.pop_back();
				inputString = inputString.substr(1);
			}
			else
			{
				std::cout << "ERROR" << std::endl;
				return false;
			}
		}
		else
		{
			if (table.find(std::make_pair(X, a)) != table.end() &&
				m_grammar.getNonTerminals().find(table.at(std::make_pair(X, a)).first) != 
				m_grammar.getNonTerminals().end())
			{
				m_stack.pop_back();
				for (auto it = table.at(std::make_pair(X, a)).second.rbegin();
						  it != table.at(std::make_pair(X, a)).second.rend();
						  it++)
				{
					if (*it != '~')
						m_stack.push_back(*it);
				}
				std::cout << X << " -> " << table.at(std::make_pair(X, a)).second << std::endl;
			}
			else
			{
				std::cout << "ERROR" << std::endl;
				return true;
			}
		}
	} while (m_stack.back() != '$');

	return true;
}