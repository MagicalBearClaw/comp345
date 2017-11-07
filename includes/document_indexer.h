#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H

#include "indexer.h"

class DocumentIndexer : public Indexer{
/**
	 * @brief overloaded extractor to stream content from a file into an indexer object.
	 * 
	 * @param ifs input file stream
	 * @param indexer indexer object
	 * @return std::ifstream allows for chaining
	 */
	friend std::ifstream &operator>>(std::ifstream &ifs, DocumentIndexer &indexer);
};

#endif //DOCUMENT_INDEXER_H