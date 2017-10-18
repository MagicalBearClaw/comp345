#include "../includes/query_result.h"

query_result::query_result(Document doc, double rank) : doc(doc), rank(rank)
{

}

Document query_result::getDocument() const
{
	return doc;
}

double query_result::getRank() const
{
	return rank;
}
