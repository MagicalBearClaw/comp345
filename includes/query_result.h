#include <string>
#include <ostream>
#include <vector>

#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

class Query_result {
/**
* @brief Overloaded Inserter
*
* Overloade inserter (operator<<) to provide meaningful debug output.
*
*/friend std::ostream & operator<<(std::ostream & os, const Query_result & result);
public:
	/**
	* @brief Default Constructor
	*
	* This is the Indexer default constructor, which creates an empty index.
	*/
	Query_result();

	/**
	* @brief Queries the indexer
	*
	* The query() function returns a vector<query result>, where each result object has a document and its score.
	*
	* @return vector<query_result> results from the query
	*/
	std::vector<Query_result> query();

	/**
	* @brief Queries the indexer with a provided string
	*
	* The function query(string, int) is used to query the index with the provided string. By
	* default, it returns the top-10 results, but this can be overridden on a per-query basis (optional second argument)
	*
	* @param std::string
	* @param int
	*
	* @return std::string the name of the document
	*/
	std::vector<Query_result> query(std::string, int);

private:
	Document
};

#endif // !QUERY_RESULT_H
