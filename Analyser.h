#pragma once

#include "Grammar.h"

class Analyser
{
public:
	explicit Analyser(const std::string& grammarFileName);
private:
	Grammar m_grammar;
};