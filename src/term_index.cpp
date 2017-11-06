#include <cmath>

#include "../includes/term_index.h"

TermIndex::TermIndex(): norm(0.0) {}

void TermIndex::indexWord(std::string word) {
  termIndexer[word] = (*this)[word] + 1;
}

int TermIndex::operator[](std::string word) {
  if (termIndexer.find(word) == termIndexer.end()) { // checks if word does not exist
		return 0;
	}
	return termIndexer[word];
}

double TermIndex::termWeight(std::string word, double documentFrequencyModifier) {
  int termCount = (*this)[word];
	return termCount ? (1 + log(termCount)) * documentFrequencyModifier : 0.0;
}

void TermIndex::normalize(const std::vector<std::string> &words, const std::vector<double> &documentModifiers, StopWord* sw) {
  double normAcc = 0.0;
	// check if a stopword reference is given
	if (sw == nullptr) {
		for (int i = 0; i != words.size(); ++i) {
			normAcc += pow(termWeight(words[i], documentModifiers[i]), 2);
		}
		
	}
	else 
	{
		for (int i = 0; i != words.size(); ++i) {
			if (!sw->operator()(words[i])) { // check that the current word *i is not a stopword before adding it to the vector
				normAcc += pow(termWeight(words[i], documentModifiers[i]), 2);
			}
		}
	}
	norm = sqrt(normAcc);
}

double TermIndex::docNorm() {
  return norm;
}