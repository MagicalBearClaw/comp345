#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H

#include "indexer.h"

class DocumentIndexer : public Indexer
{
	/**
	 * @brief overloaded extractor to stream content from a file into an indexer object.
	 * 
	 * @param ifs input file stream
	 * @param indexer indexer object
	 * @return std::ifstream allows for chaining
	 */
	friend std::ifstream &operator>>(std::ifstream &ifs, DocumentIndexer &indexer);
	/**
	 * @brief 
	 * 
	 * @param ios 
	 * @param indexer 
	 * @return std::ostream& 
	 */
	friend std::ostream &operator<<(std::ostream &ios, DocumentIndexer &indexer);
	/**
	 * @brief 
	 * 
	 * @param doc 
	 * @param indexer 
	 */
	friend void operator>>(Document &doc, DocumentIndexer &indexer);

  public:
	/**
	 * @brief 
	 * 
	 */
	typedef std::tuple<std::string, int, double> wordFrequencyTermMod;
	/**
	 * @brief 
	 * 
	 */
	virtual void normalize();
	/**
	 * @brief 
	 * 
	 * @param queryString 
	 * @param numOfResults 
	 * @return std::vector<query_result> 
	 */
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

  private:
	// tuple of words their index_item frequency and the modifier to compute the weight of a term
	std::vector<wordFrequencyTermMod> wftms;
	int maxWordLength; /**Ctr used for display of word column*/
	/**
	* @brief the document frequency dft for a term t is defined as the number of documents that t appears in
	*
	* This member function is used to count the total number of documents that a word appears in
	* @param word the word to caluclate the frequency for
	* @return int the documentFrequency for the specified word
	*/
	virtual int calculateDocumentFrequency(std::string term);

};

#endif //DOCUMENT_INDEXER_H