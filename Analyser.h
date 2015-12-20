#pragma once

#include "Grammar.h"

#include <vector>

class Analyser
{
public:
	explicit Analyser(const std::string& grammarFileName);
	const Grammar& getGrammar() const;
	void parseFromFile(const std::string& fileName);
	int getErrorCount() const;
private:
	Grammar m_grammar;
	std::string m_stack;
	int m_errorCount;
};