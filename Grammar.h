#pragma once

#include <string>
#include <map>
#include <set>

class Grammar
{
public:
	explicit Grammar(const std::string& fileName);
	const std::map<char, std::set<char>>& getFirst() const;
	const std::map<char, std::set<char>>& getFollow() const;
private:
	void generateFirst();
	void generateFollow();
	std::multimap<char, std::string> m_rules;
	std::set<char> m_terminals;
	std::set<char> m_nonTerminals;
	std::map<char, std::set<char>> m_first;
	std::map<char, std::set<char>> m_follow;
};