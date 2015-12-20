#pragma once

#include "Grammar.h"

class Analyser
{
public:
	explicit Analyser(const std::string& grammarFileName);
	const Grammar& getGrammar() const;
	bool isAcceptable(const std::string& fileName) const;
private:
	Grammar m_grammar;
};