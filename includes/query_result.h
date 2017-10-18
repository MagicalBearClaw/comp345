#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include "../includes/document.h"

class query_result 
{
public:
	query_result(Document doc, double rank);
	Document getDocument() const;
	double getRank() const;
private:
	Document doc;
	double rank;

};

#endif // !QUERY_RESULT_H
