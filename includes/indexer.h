#ifndef INDEXER_H
#define INDEXER_H

#include <tuple>

#include "../includes/index item.h"
#include "../includes/query_result.h"
#include "../includes/term_index.h"

/**
 * @brief The starting point of the program
 * 
 * @return int 0 if all went well.
 */
int main();


/**
 * The Indexer class is responsible for storing and maintaining a index item.
 *
 */
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
	 * @brief returns the number of items in the index.
	 *
	 * This function size() returns the number of index items stored within this indexer class.
	 *
	 * @return int	The number of index items in the index.
	 */
	int size();
	/**
	* @brief computes the tf-idf weights based on the number N of indexed index items
	*
	* This function normalize() computes the tf-idf weights based on the number N of indexed index items.
	* These weights are storied inside the indexer.
	*
	*/
	virtual void normalize() = 0;

	/**
	* @brief Overloaded array access operator to retrieve index item by index
	*
	* This class provides access to its indexed index items with an overloaded operator[]: 
	* e.g., idx[3] would return the fourth index item in the index, as an object of class index item.
	*
	* @return Index_item*	The selected index item object as requested by index.
	*/
	Index_item operator[](int position);

	/**
	 * @brief Returns if the provided inedxer is normalized
	 * 
	 * @param indexer 
	 * @return true 
	 * @return false 
	 */
	bool isNormalized(Indexer& indexer);
	/**
	 * @brief function returns a vector<query result>, where each result object has a index item and its score
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
	// the index_item and it's associated TermIndex (meta data to compute weight)
	typedef std::tuple<Index_item*, TermIndex>  itemTermIndex;
	std::vector<std::tuple<Index_item*, TermIndex>> itis;
	int index itemCount; /**The number of index items in the index*/

	int maxColumnSize; /**ctr used for display of count columns*/
	bool normalized; /** Status check if the index has been normalized*/
	std::vector<index item> index items; /** vector of all index items*/
	std::vector<std::string> docNames; /** vector of all index item names*/
									   // std::vector<std::string> allWords; //**all words in the index*/
	std::vector<double> docTermModifiers; /**log(documentnetCount/index itemFrequency)*/
	std::vector<int> docTermFrequency; /**how many index items contain the word*/
	std::vector<TermIndex> index itemIndices;
	virtual int calculateindex itemFrequency(std::string term) = 0;

};

#endif // INDEXER_H
