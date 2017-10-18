#ifndef INDEXER_H
#define INDEXER_H

#include "../includes/document.h"
#include "../includes/query_result.h"

int main();

/**
 * The Indexer class is responsible for storing and maintaining a document index.
 *
 */
class Indexer
{
	/**
	 * @brief overloaded extractor to stream content from a file into an indexer object.
	 * 
	 * @param ifs input file stream
	 * @param indexer indexer object
	 * @return std::ifstream allows for chaining
	 */
	friend std::ifstream &operator>>(std::ifstream &ifs, Indexer &indexer);
	/**
	 * @brief overloaded inserter to print out the contents of an indexer object to a stream
	 * 
	 * @param ios output stream to insert content into
	 * @param indexer object to stream content out from
	 * @return std::ostream allows for chaining
	 */
	friend std::ostream &operator<<(std::ostream &ios, Indexer &indexer);
	/**
	 * @brief overloaded extractor operator used to extract the content of a document into an indexer
	 * 
	 * This function is an alternative way to add a document to an indexer object.
	 * This functions primary purpose is used to build the indexers documentIndex
	 * by streaming in documentes one at a time.
	 * 
	 * @param doc the document to add to the index
	 * @param indexer the indexer to add a document to
	 */
	friend void operator>>(Document &doc, Indexer &indexer);

  public:
	/** 
	 * Default Constructor
	 *
	 * This is the Indexer default constructor, which creates an empty index.
	 */
	Indexer();
	/** @brief Desctructor for Indexer class*/
	~Indexer();
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
	void normalize();

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
	std::vector<query_result> query(std::string queryString, int numOfResults = 10);
private:
	int documentCount; /**The number of documents in the index*/
	int maxWordLength; /**Ctr used for display of word column*/
	int maxColumnSize; /**ctr used for display of count columns*/
	bool normalized; /** Status check if the index has been normalized*/
	std::vector<Document> documentIndex; /** vector of all documents*/
	std::vector<std::string> docNames; /** vector of all document names*/
	std::vector<std::string> allWords; //**all words in the index*/
	std::vector<double> docTermModifiers; /**log(documnetCount/documentFrequency)*/
	std::vector<int> docTermFrequency; /**how many documents contain the word*/

	/**
	 * @brief the document frequency dft for a term t is defined as the number of documents that t appears in
	 * 
	 * This member function is used to count the total number of documents that a word appears in
	 * @param word the word to caluclate the frequency for
	 * @return int the documentFrequency for the specified word
	 */
	int calculateDocumentFrequency(std::string word);
};

#endif
