#include <cmath>

#include "../includes/term_index.h"

TermIndex::TermIndex() : norm(0.0) {}

void TermIndex::indexWord(std::string& word)
{
	termIndexer[word] = (*this)[word] + 1;
}

int TermIndex::operator[](const std::string& word)
{
	if (termIndexer.find(word) == termIndexer.end())
	{ // checks if word does not exist
		return 0;
	}
	return termIndexer[word];
}

double TermIndex::termWeight(std::string word, double documentFrequencyModifier)
{
	int termCount = (*this)[word];
	return termCount ? (1 + log(termCount)) * documentFrequencyModifier : 0.0;
}

void TermIndex::normalize(const std::unordered_map<std::string, std::tuple<std::string, int, double>> &wftms, StopWord *sw)
{
	double normAcc = 0.0;
	// check if a stopword reference is given
	if (sw == nullptr)
	{
		for (std::unordered_map<std::string, int>::const_iterator i = termIndexer.begin(); i != termIndexer.end(); ++i)
		{
			// std::string w = std::get<0>(*i);
			const std::tuple<std::string, int, double> wftm = (wftms.find(i->first))->second;
			normAcc += pow(termWeight(i->first, std::get<1>(wftm)), 2);
		}
	}
	else
	{
		for (std::unordered_map<std::string, int>::const_iterator i = termIndexer.begin(); i != termIndexer.end(); ++i)
		{
			// std::string w = std::get<0>(*i);
			if (!sw->operator()(i->first))
			{
				const std::tuple<std::string, int, double> wftm = (wftms.find(i->first))->second;
				normAcc += pow(termWeight(i->first, std::get<1>(wftm)), 2);
			}
		}
	}
	norm = sqrt(normAcc);
}

double TermIndex::docNorm()
{
	return norm;
}