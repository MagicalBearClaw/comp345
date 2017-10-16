#include <map>
#include <assert.h>
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <ostream>
#include <iomanip>
#include <cmath>

#include "document.h"

#ifndef INDEXER_H
#define INDEXER_H

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
public:
	/** 
	 * @brief Default Constructor
	 *
	 * This is the Indexer default constructor, which creates an empty index.
	 */
	Indexer();
    /** @brief Desctructor for Indexer class*/
	~Indexer();
	Document* operator[](std::string docName);
	void createDocument(std::string& name);
	void addWord(std::string& docName, std::string& word);
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
	*
	* @return int	The calculated tf-idf weight
	*/
	int normalize();

	/**
	* @brief Overloaded array access operator to retrieve document by index
	*
	* This class provides access to its indexed documents with an overloaded operator[]: 
	* e.g., idx[3] would return the fourth document in the index, as an object of class document.
	*
	* @return Document*	The selected document object as requested by index.
	*/
	Document* operator[] (int position);
private:
	int documentCount; /**The number of documents in the index*/
	int maxWordLength;
	std::map<std::string, Document*> documents;
	std::vector<std::string> words;
	std::vector<std::string> docNames;
	
	/**
	* @brief
	*
	* Term Frequency is the word count denoted by tf_td, where t is a term (token) in the dictionary and d is a document that was indexed.
	*
	* return
	*/
	double calulateTermFrequency();
	/**
	* @brief
	*
	* the document frequency dft for a term t is defined as the number of documents that t appears in
	*/
	double calculateDocumentFrequency(std::string word);

	/**
	*
	* @brief
	*
	* return
	*/
	double calculateTFidf(double termFrequency, double documentFrequency);

};

#endif
