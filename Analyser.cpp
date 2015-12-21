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

void Analyser::parseFromFile(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	std::string inputString = "";
	std::string line;
	while (std::getline(inputFile, line))
	{
		inputString += line;
	}
	//int pos = 0;
	/*
	while ((pos = inputString.find(" ")) != std::string::npos)
	{
		inputString.replace(pos, 1, "");
	}
	*/
	inputString.push_back('$');

	m_stack.clear();
	m_stack.push_back('$');
	m_stack.push_back(m_grammar.getFirstNonTerminal());

	m_errorCount = 0;

	auto table = m_grammar.getTable();
	std::string error = "";
	bool inError = false;

	do
	{
		char X = m_stack.back();
		char a = inputString.front();
		error = "";
		if (m_grammar.getTerminales().find(m_stack.back()) != m_grammar.getTerminales().end())
		{
			if (X == a)
			{
				std::cout << m_stack << " | " << inputString << " | " << error << std::endl;
				m_stack.pop_back();
				inputString = inputString.substr(1);
			}
			else
			{
				error = "Syntax ERROR";
				std::cout << m_stack << " | " << inputString << " | " << error << std::endl;
				m_stack.pop_back();
				inError = true;
				m_errorCount++;
			}
		}
		else
		{
			if (table.find(std::make_pair(X, a)) != table.end() &&
				m_grammar.getNonTerminals().find(table.at(std::make_pair(X, a)).first) != 
				m_grammar.getNonTerminals().end())
			{
				std::cout << m_stack << " | " << inputString << " | " << error << std::endl;

				m_stack.pop_back();
				for (auto it = table.at(std::make_pair(X, a)).second.rbegin();
						  it != table.at(std::make_pair(X, a)).second.rend();
						  it++)
				{
					if (*it != '~')
						m_stack.push_back(*it);
				}
			}
			else
			{
				if (table.at(std::make_pair(X, a)).first == 0)
				{
					error = "Error: Skip symbol";
					std::cout << m_stack << " | " << inputString << " | " << error << std::endl;
					inputString = inputString.substr(1);
					inError = true;
					m_errorCount++;
				}
				else
				if (table.at(std::make_pair(X, a)).first == 1 && inError)
				{
					error = "Synched";
					std::cout << m_stack << " | " << inputString << " | " << error << std::endl;
					m_stack.pop_back();
					inError = false;
				}
			}
		}
		
	} while (m_stack.back() != '$' && !inputString.empty());
	if (inputString.empty())
	{
		inError = true;
		error = "Syntax error";
		m_errorCount++;
	}
	std::cout << m_stack << " | " << inputString << " | " << error << std::endl;
}

int Analyser::getErrorCount() const
{
	return m_errorCount;
}