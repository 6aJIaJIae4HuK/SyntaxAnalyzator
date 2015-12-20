#include "Grammar.h"

#include <fstream>

Grammar::Grammar(const std::string& fileName)
{
	std::ifstream input(fileName);
	std::string line;
	int pos = std::string::npos;
	while (std::getline(input, line))
	{
		pos = line.find('>');
		if (pos != 1 || !(line[0] >= 'A' && line[0] <= 'Z'))
			throw ("Incorrect line!!");
		m_nonTerminals.insert(line[0]);

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
	}
	generateFirst();
	generateFollow();
}

void Grammar::generateFirst()
{
	for (auto it = m_terminals.begin(); it != m_terminals.end(); it++)
	{
		m_first[*it].insert(*it);
	}
	for (auto it = m_rules.begin(); it != m_rules.end(); it++)
	{
		if (it->second == "$")
			m_first[it->first].insert('$');
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
				if (m_first[*it].find('$') == m_first[*it].end())
				{
					existsEmpty = false;
				}
				for (auto it1 = m_first[*it].begin(); it1 != m_first[*it].end(); it1++)
				{
					if (m_first[rule->first].insert(*it1).second)
					{
						changed = true;
					}
				}
			}
			if (existsEmpty)
			{
				if (m_first[rule->first].insert('$').second)
				{
					changed = true;
				}
			}
		}
	}
}

void Grammar::generateFollow()
{

}

const std::map<char, std::set<char>>& Grammar::getFirst() const
{
	return m_first;
}

const std::map<char, std::set<char>>& Grammar::getFollow() const
{
	return m_follow;
}