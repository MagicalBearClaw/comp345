//#include "../includes/indexer.h"
//
//int main(){
//
//    const int maxWordCount = 500;
//    Indexer *idx1 = new Indexer();
//    //index each of the source documents in set 1 (q1docs)
//    //Build query of essay topic q1.txt
//
//
//    // {FUTURE TEST CASES}
//    // Indexer *idx2 = new Indexer();
//    // //index each of the source documents in set 2 (q2docs)
//    // //Build query of essay topic q2.txt
//    // Indexer *idx3 = new Indexer();
//    // //index each of the source documents in set 3 (q3docs)
//    // //Build query of essay topic q3.txt
//
//    
//
//    
//
//}


#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

#include "../includes/indexer.h"
#include "../includes/document_indexer.h"
#include "../includes/sentence_indexer.h"
#include "../includes/query_result.h"

int main()
{
	int numOfResults = 10;
	Indexer *dIdx = new DocumentIndexer();
	//TODO: change this to read one of topic sentence.
	std::ifstream ifs("resources/index.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *dynamic_cast<DocumentIndexer*>(dIdx);
	}
	
	std::ifstream queries("resources/a3index.txt");
	assert(queries.good() && "Invalid file name");
	while (!queries.eof())
	{
		Indexer *idx = new Sentence_indexer();
		std::string query;
		queries >> query;
		std::cout << "Essay for: " << query << std::endl;
		std::vector<query_result> releventDocs = dIdx->query(query, 5);
		for (std::vector<query_result>::iterator result = releventDocs.begin(); result != releventDocs.begin(); ++result) {
			result->getItem() >> *dynamic_cast<Sentence_indexer*>(idx);
		}
		std::vector<query_result> relevantSentences = idx->query(query);
		for(std::vector<query_result>::iterator sentence = relevantSentences.begin(); sentence != relevantSentences.end(); ++sentence) {
			std::cout << sentence->getItem()->content() << " ";
		}
		std::cout << std::endl;
		delete idx;
	}
	// idx->generate_essay();
	//std::cout << idx; // display essay

	return 0;
}