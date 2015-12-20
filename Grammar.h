#pragma once

#include <string>
#include <map>
#include <set>

class Grammar
{
public:
	explicit Grammar(const std::string& fileName);
	const std::map<std::string, std::set<char>>& getFirst() const;
	const std::map<char, std::set<char>>& getFollow() const;
private:
	std::string toString(const char& c) const;
	void generateFirst();
	void generateFirst(const std::string& chain);
	void generateFollow();
	char m_firstNonTerminal;
	std::multimap<char, std::string> m_rules;
	std::set<char> m_terminals;
	std::set<char> m_nonTerminals;
	std::map<std::string, std::set<char>> m_first;
	std::map<char, std::set<char>> m_follow;
};