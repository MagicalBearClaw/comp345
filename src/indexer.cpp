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
