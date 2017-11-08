#include "../includes/sentence_indexer.h"

std::ifstream &operator >> (std::ifstream &ifs, Sentence_indexer &indexer)
{
	return ifs;
}
std::ostream & operator<<(std::ostream &ios, Sentence_indexer &indexer)
{
	return ios;
}
void operator >> (Document &doc, Sentence_indexer &indexer)
{

}

Sentence_indexer::Sentence_indexer()
{

}

Sentence_indexer::~Sentence_indexer()
{

}

void Sentence_indexer::normalize()
{

}
std::vector<query_result> Sentence_indexer::query(std::string queryString, int numOfResults)
{
	return std::vector<query_result>();
}

int Sentence_indexer::calculateDocumentFrequency(std::string term)
{
	return 0;
}
