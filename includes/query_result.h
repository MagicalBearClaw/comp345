#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include "../includes/document.h"

/**
* The query_result class is responsible to keep the state of its ranks
* as well as the document that the query apears in.
*
*/
class query_result 
{
public:
	/**
	 * @brief constructor for a query result object
	 * 
	 * A query_result object is a key value pair that links a document to its rank.
	 * 
	 * @param doc the document
	 * @param rank  the rank
	 */
	query_result(Document doc, double rank);
	/**
	 * @brief accessor method to return a document
	 * 
	 * @return Document the document associated with this query.
	 */
	Document getDocument() const;
	/**
	 * @brief accessor method to return a rank
	 * 
	 * @return double the rank associated with this query.
	 */
	double getRank() const;
private:
	Document doc;
	double rank;

};

#endif // !QUERY_RESULT_H
