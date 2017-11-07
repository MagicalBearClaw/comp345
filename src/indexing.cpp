#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

#include "../includes/app.h"
#include "../includes/indexer.h"

int main(void)
{
	//An object idx of class indexer holds the data structures created from the input documents
	//New creates object on stack and returns a pointer
	Indexer *idx = new Indexer();
	std::ifstream ifs("resources/index.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *idx;
	}
	std::cout << *idx;

	return 0; //All went well.
}