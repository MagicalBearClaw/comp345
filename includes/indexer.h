#ifndef INDEXER_H
#define INDEXER_H

#include <tuple>

#include "../includes/document.h"
#include "../includes/query_result.h"
#include "../includes/term_index.h"

int main();


/**
 * The Indexer class is responsible for storing and maintaining a document index.
 *
 */
//TODO this should now become an abstract base class
class Indexer
{
  public:
	/** 
	 * Default Constructor
	 *
	 * This is the Indexer default constructor, which creates an empty index.
	 */
	Indexer();
	/** @brief Desctructor for Indexer class*/
	virtual ~Indexer();
	/**
	 * @brief returns the number of documents in the index.
	 *
	 * This function size() returns the number of documents stored within this indexer class.
	 *
	 * @return int	The number of documents in the index.
	 */
	int size();
	/**
	* @brief computes the tf-idf weights based on the number N of indexed documents
	*
	* This function normalize() computes the tf-idf weights based on the number N of indexed documents.
	* These weights are storied inside the indexer.
	*
	*/
	virtual void normalize();
	
	/**
	 * @brief Overloaded array access operator to retrieve document by index
	 *
	 * This class provides access to its indexed documents with an overloaded operator[]: 
	 * e.g., idx[3] would return the fourth document in the index, as an object of class document.
	 *
	 * @return Document*	The selected document object as requested by index.
	 */
	Document operator[](int position);
	
	/**
	 * @brief Returns if the provided inedxer is normalized
	 * 
	 * @param indexer 
	 * @return true 
	 * @return false 
	 */
	bool isNormalized(Indexer& indexer);
	/**
	 * @brief function returns a vector<query result>, where each result object has a document and its score
	 * 
	 * This function query(string, int) is used to query the index with the provided string. By
	 * default, it returns the top-10 results, but this can be overridden on a per-query basis (optional second
	 * argument).
	 * 
	 * @param queryString the query string that is entered by the user
	 * @param numOfResults number of results to return defaulted to 10
	 * @return std::vector<query_result> 
	 */
	virtual std::vector<query_result> query(std::string queryString, int numOfResults = 10) = 0;
protected:
	virtual int calculateDocumentFrequency(std::string term);
	// the index_item and it's associated TermIndex (meta data to compute weight)
	typedef std::tuple<Index_item*, TermIndex>  itemTermIndex;
	typedef std::tuple<std::string, int, double> wordFrequencyTermMod;
	std::vector<std::tuple<Index_item*, TermIndex>> itis;
	int documentCount; /**The number of documents in the index*/
	
	int maxColumnSize; /**ctr used for display of count columns*/
	bool normalized; /** Status check if the index has been normalized*/
	std::vector<Document> documents; /** vector of all documents*/
	std::vector<std::string> docNames; /** vector of all document names*/
	// std::vector<std::string> allWords; //**all words in the index*/
	std::vector<double> docTermModifiers; /**log(documnetCount/documentFrequency)*/
	std::vector<int> docTermFrequency; /**how many documents contain the word*/
	std::vector<TermIndex> documentIndices;
	std::vector<wordFrequencyTermMod> wftms;

};

#endif // INDEXER_H
