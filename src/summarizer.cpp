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


#include "../includes/indexer.h"
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "../includes/sentence_indexer.h"
int main()
{
	int numOfResults = 10;
	Sentence_indexer *idx = new Sentence_indexer();
	//TODO: change this to read one of topic sentence.
	std::ifstream ifs("resources/index.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *(Sentence_indexer*)idx;
	}
	// idx->generate_essay();
	//std::cout << idx; // display essay

	return 0;
}