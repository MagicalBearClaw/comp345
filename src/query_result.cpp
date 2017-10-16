#include <tokenizer.h>

#include "query_result.h"
// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2933888/mod_resource/content/1/a2.pdf

Query_result::Query_result() {

}

std::vector<Query_result> Query_result::query()
{

	// Processing the Query: Convert the query into the same vector representation as the documents. The result
	//is a query vector ~q.Tokens from the input query that do not appear in the indexed documents are simply ignored.	//Document ranking: Now we have to find the documents that best match the query.This is done using a
		//scoring function as follows : For each document dj in your index, compute the cosine similarity between the
		//document vector ~dj and the query vector ~q as
	return std::vector<Query_result>();
}

std::vector<Query_result> Query_result::query(std::string, int)
{
	return std::vector<Query_result>();
}

std::ostream & operator<<(std::ostream &os, Query_result &result) {
}
