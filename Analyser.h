#pragma once

#include "Grammar.h"

#include <vector>

class Analyser
{
public:
	explicit Analyser(const std::string& grammarFileName);
	const Grammar& getGrammar() const;
	bool isAcceptable(const std::string& fileName);
private:
	Grammar m_grammar;
	std::vector<char> m_stack;

};