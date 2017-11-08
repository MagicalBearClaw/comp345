#include "../includes/indexer.h"
#include "../includes/util.h"
#include "../includes/word_tokenizer_strategy.h"
#include "../includes/tokenizer.h"


#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <iterator>


Indexer::Indexer()
  : documentCount(0), normalized(false), maxColumnSize(18)
{}

Indexer::~Indexer() {}

// same functionality
int Indexer::size() {
	return documentCount;
	//return documentIndex.size();
}

// same functionality
bool Indexer::isNormalized(Indexer& indexer) {
	return normalized;
}
// same functionality (index item*)
Document Indexer::operator[](int position)
{
	return documents[position];
}

// A function normalize() computes the tf-idf weights based on the number N of indexed documents.
// can be implemented on base class
void Indexer::normalize()
{
	int termFrequency = 0;
	int documentFrequency = 0;
	double dtModifier = 0.0;

	for (std::vector<wordFrequencyTermMod>::iterator iter = wftms.begin(); iter != wftms.end(); ++iter) {

		documentFrequency = calculateDocumentFrequency(std::get<0>(*iter));

		dtModifier = std::log((double)documentCount / (double)documentFrequency);
		std::get<1>(*iter) = documentFrequency;
		std::get<2>(*iter) = dtModifier;
		// docTermModifiers.push_back(dtModifier);
		// docTermFrequency.push_back(documentFrequency);
	}
	double weight;
	int maxAcc;
	for (std::vector<itemTermIndex>::iterator iter = itis.begin(); iter != itis.end(); ++iter) {
		std::get<1>(*iter).normalize(wftms);
		// iter->normalize(allWords, docTermModifiers);
		// verify that column size values are not suppased (this is for rendering the table later on)
		maxAcc = 0;
		for (std::vector<wordFrequencyTermMod>::iterator word = wftms.begin(); word != wftms.end(); ++word) {
			maxAcc += std::get<1>(*iter)[std::get<0>(*word)];
			weight = std::get<1>(*iter).termWeight(std::get<0>(*word), std::get<2>(*word)); // iter->termWeight(*word, docTermModifiers[word - allWords.begin()]);
			if (std::to_string(weight).length() > maxColumnSize / 2 - maxColumnSize % 2) {
				maxColumnSize = std::to_string(weight).length() * 2 + 2;
			}
		}
		if (std::to_string(maxAcc).length() > maxColumnSize) {
			maxColumnSize = std::to_string(maxAcc).length();
		}
	}
	normalized = true;
}

int Indexer::calculateDocumentFrequency(std::string word) {
	int docFrequencyAcc = 0;
	for (std::vector<itemTermIndex>::iterator iter = itis.begin(); iter != itis.end(); ++iter) {
		docFrequencyAcc += std::get<1>(*iter)[word] ? 1 : 0;
	}

	return docFrequencyAcc;
}
