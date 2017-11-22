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

double TermIndex::termWeight(std::string& word, double documentFrequencyModifier)
{
	int termCount = (*this)[word];
	return termCount ? (1 + log(termCount)) * documentFrequencyModifier : 0.0;
}

void TermIndex::normalize(const std::vector<std::tuple<std::string, int, double>> &wftms, StopWord *sw)
{
	double normAcc = 0.0;
	// check if a stopword reference is given
	if (sw == nullptr)
	{
		for (std::vector<std::tuple<std::string, int, double>>::const_iterator i = wftms.begin(); i != wftms.end(); ++i)
		{
			std::string w = std::get<0>(*i);
			normAcc += pow(termWeight(w, std::get<1>(*i)), 2);
		}
	}
	else
	{
		for (std::vector<std::tuple<std::string, int, double>>::const_iterator i = wftms.begin(); i != wftms.end(); ++i)
		{
			std::string w = std::get<0>(*i);
			if (!sw->operator()(std::get<0>(*i)))
			{
				normAcc += pow(termWeight(w, std::get<1>(*i)), 2);
			}
		}
	}
	norm = sqrt(normAcc);
}

double TermIndex::docNorm()
{
	return norm;
}