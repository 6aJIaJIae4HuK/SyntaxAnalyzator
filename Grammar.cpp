#include "Grammar.h"

#include <fstream>

Grammar::Grammar(const std::string& fileName)
{
	std::ifstream input(fileName);
	std::string line;
	int pos = std::string::npos;
	bool first = true;
	while (std::getline(input, line))
	{
		pos = line.find('>');
		if (pos != 1 || !(line[0] >= 'A' && line[0] <= 'Z'))
			throw ("Incorrect line!!");
		m_nonTerminals.insert(line[0]);

		if (first)
			m_firstNonTerminal = line[0];

		std::string right = line.substr(2);
		auto l = right.begin();
		for (auto it = right.begin(); it != right.end(); it++)
		{
			if (*it >= 'A' && *it <= 'Z')
			{
				m_nonTerminals.insert(*it);
			}
			else
				if (*it == '|')
				{
					m_rules.insert(std::make_pair(line[0], std::string(l, it)));
					l = it;
					l++;
				}
				else
				{
					m_terminals.insert(*it);
				}
		}
		m_rules.insert(std::make_pair(line[0], std::string(l, right.end())));
		first = false;
	}
	generateFirst();
	generateFollow();
}

void Grammar::generateFirst()
{
	m_first[""].insert('~');
	for (auto it = m_terminals.begin(); it != m_terminals.end(); it++)
	{
		m_first[toString(*it)].insert(*it);
	}
	for (auto it = m_rules.begin(); it != m_rules.end(); it++)
	{
		if (it->second == "~")
			m_first[toString(it->first)].insert('~');
	}
	bool changed = true;
	while (changed)
	{
		changed = false;
		for (auto rule = m_rules.begin(); rule != m_rules.end(); rule++)
		{
			std::string& chain = rule->second;
			bool existsEmpty = true;
			for (auto it = chain.begin(); it != chain.end() && existsEmpty; it++)
			{
				if (m_first[toString(*it)].find('~') == m_first[toString(*it)].end())
				{
					existsEmpty = false;
				}
				for (auto it1 = m_first[toString(*it)].begin(); it1 != m_first[toString(*it)].end(); it1++)
				{
					if (*it1 != '~' && m_first[toString(rule->first)].insert(*it1).second)
					{
						changed = true;
					}
				}
			}
			if (existsEmpty)
			{
				if (m_first[toString(rule->first)].insert('~').second)
				{
					changed = true;
				}
			}
		}
	}
}

void Grammar::generateFirst(const std::string& chain)
{
	if (m_first.find(chain) != m_first.end())
		return;
	m_first.insert(std::make_pair(chain, std::set<char>()));
	bool existEmpty = true;
	for (auto it = chain.begin(); it != chain.end() && existEmpty; it++)
	{
		if (m_first[toString(*it)].find('~') == m_first[toString(*it)].end())
		{
			existEmpty = false;
		}
		for (auto it1 = m_first[toString(*it)].begin(); it1 != m_first[toString(*it)].end(); it1++)
		{
			if (*it1 != '~')
				m_first[chain].insert(*it1);
		}
	}
	if (existEmpty)
		m_first[chain].insert('~');
}

void Grammar::generateFollow()
{
	m_follow[m_firstNonTerminal].insert('$');
	for (auto rule = m_rules.begin(); rule != m_rules.end(); rule++)
	{
		for (auto it = rule->second.begin(); it != rule->second.end(); it++)
		{
			if (m_nonTerminals.find(*it) != m_nonTerminals.end())
			{
				it++;
				std::string chain = std::string(it, rule->second.end());
				generateFirst(chain);
				it--;
				for (auto it1 = m_first[chain].begin(); it1 != m_first[chain].end(); it1++)
				{
					if (*it1 != '~')
					{
						m_follow[*it].insert(*it1);
					}
				}
			}
		}
	}
	bool changed = true;
	while (changed)
	{
		changed = false;
		for (auto rule = m_rules.begin(); rule != m_rules.end(); rule++)
		{
			for (auto it = rule->second.begin(); it != rule->second.end(); it++)
			{
				if (m_nonTerminals.find(*it) != m_nonTerminals.end())
				{
					it++;
					std::string chain = std::string(it, rule->second.end());
					generateFirst(chain);
					it--;
					if (m_first[chain].find('~') != m_first[chain].end())
					{
						for (auto it1 = m_follow[rule->first].begin(); it1 != m_follow[rule->first].end(); it1++)
						{
							if (m_follow[*it].insert(*it1).second)
							{
								changed = true;
							}
						}
					}
				}
			}
		}
	}
}

const std::map<std::string, std::set<char>>& Grammar::getFirst() const
{
	return m_first;
}

const std::map<char, std::set<char>>& Grammar::getFollow() const
{
	return m_follow;
}

std::string Grammar::toString(const char& c) const
{
	std::string res = "";
	res += c;
	return res;
}