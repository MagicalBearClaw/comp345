

#ifndef INDEXER_H
#define INDEXER_H

#include "../includes/document.h"
#include "../includes/query_result.h"
// typedef std::map<std::string, int> WordCtr; // find better name

int main();

// void indexWord(WordCtr& dict, std::string& word);

// should keep track of largest word for styling

/**
 * The Indexer class is responsible for storing and maintaining a document index.
 *
 */
class Indexer {
	friend std::ifstream & operator>>(std::ifstream &ifs, Indexer &indexer);
	friend std::ostream & operator<<(std::ostream &ios, Indexer &indexer);
	friend void operator>>(Document &doc, Indexer &indexer);
public:
	/** 
	 * @brief Default Constructor
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
	Document operator[] (int position);

	/**
	 * @brief Returns if the provided inedxer is normalized
	 * 
	 * @param indexer 
	 * @return true 
	 * @return false 
	 */
	bool isNormalized(Indexer& indexer);
	std::vector<query_result> query(std::string queryString, int numOfResults = 10);
private:
	int documentCount; /**The number of documents in the index*/
	int maxWordLength;
	bool normalized; /** Status check if the index has been normalized*/
	std::vector<Document> documentIndex;
	//std::vector<std::string> words;
	std::vector<std::string> docNames;
	std::vector<std::string> allWords;
	std::vector<double> docTermModifiers; // log(documnetCount/documentFrequency)
	std::vector<int> docTermFrequency;
	
	/**
	* @brief
	*
	* Term Frequency is the word count denoted by TF_td, where t is a term (token) in the dictionary and d is a document that was indexed.
	*
	* return
	*/
	//double calulateTermFrequency();

	/**
	 * @brief the document frequency dft for a term t is defined as the number of documents that t appears in
	 * 
	 * @param word 
	 * @return int 
	 */
	int calculateDocumentFrequency(std::string word);

};

#endif
