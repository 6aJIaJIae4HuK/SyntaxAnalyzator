#include "Analyser.h"

Analyser::Analyser(const std::string& grammarFileName) : m_grammar(grammarFileName)
{

}

const Grammar& Analyser::getGrammar() const
{
	return m_grammar;
}

bool Analyser::isAcceptable(const std::string& fileName) const
{
	return false;
}