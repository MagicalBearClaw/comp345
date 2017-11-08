//#include <string>
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include <cassert>
//
//#include "../includes/indexing.h"
//#include "../includes/indexer.h"
//#include "../includes/document_indexer.h"
//int main(void)
//{
//	//TODO: need to fix the display of indexing.
//	//An object idx of class indexer holds the data structures created from the input documents
//	//New creates object on stack and returns a pointer
//	Indexer *idx = new DocumentIndexer();
//	std::ifstream ifs("resources/index.txt");
//	assert(ifs.good() && "Invalid file name");
//	while (!ifs.eof())
//	{
//		ifs >> *(DocumentIndexer*)idx;
//	}
//	std::cout << *(DocumentIndexer*)idx;
//
//	delete idx;
//	return 0; //All went well.
//}