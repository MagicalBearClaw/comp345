#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H

#include "indexer.h"

/**
 * @brief The DocumentIndexer class is responsible for storing and maintaining a document index item.
 * 
 */
class DocumentIndexer : public Indexer
{
	/**
	 * @brief overloaded extractor to stream content from a file into an indexer object.
	 * 
	 * @param ifs input file stream
	 * @param indexer indexer object
	 * @return std::ifstream allows for chaining
	 */
	friend std::ifstream &operator >> (std::ifstream &ifs, DocumentIndexer &indexer);
	friend std::ostream & operator<<(std::ostream &ios, DocumentIndexer &indexer);
	friend void operator >> (Document &doc, DocumentIndexer &indexer);
public:
	// virtual void normalize();
	virtual std::vector<query_result> query(std::string queryString, int numOfResults = 10);
	/**
	 * @brief Default Constructor
	 * 
	 */
	DocumentIndexer();
	/**
	 * @brief Default Deconstructor
	 * 
	 */
	~DocumentIndexer();
};

#endif //DOCUMENT_INDEXER_H