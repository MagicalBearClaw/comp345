#ifndef SENTENCE_INDEXER_H
#define SENTENCE_INDEXER_H

#include "indexer.h"

class Sentence_indexer : public Indexer{
	// friend std::ifstream &operator >> (std::ifstream &ifs, Sentence_indexer &indexer);
	friend std::ostream & operator<<(std::ostream &ios, Sentence_indexer &indexer);
	friend void operator >> (IndexItem* doc, Sentence_indexer &indexer);
public:
	// typedef std::tuple<std::string, int, double> wordFrequencyTermMod;
	// virtual void normalize();
	virtual std::vector<query_result> query(std::string queryString, int numOfResults = 10);
	Sentence_indexer();
	~Sentence_indexer();
private:
	// tuple of words their IndexItem frequency and the modifier to compute the weight of a term

	// virtual int calculateDocumentFrequency(std::string term);
};

#endif //SENTENCE_INDEXER_H