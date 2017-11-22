#include "../includes/indexer.h"
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "../includes/movie_indexer.h"
int main()
{
	int numOfResults = 5;
	Indexer *idx = new MovieIndexer();
	std::ifstream ifs("resources/movie_indexer.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *(MovieIndexer*)idx;
	}
	ifs.close();
	std::string buffer = "";
	while (true)
	{
		buffer.clear();
		std::cout << "Please enter a movie name so we can give you more recomendations based on your likings.." << std::endl;
 		std::getline(std::cin, buffer);
		if (buffer.empty())
			continue;
		else if (buffer == "!q")
			break;

		idx->normalize();
		std::vector<query_result> ranks = idx->query(buffer, numOfResults);
		int maxLength = ranks[0].getItem()->name().size();
		std::sort(ranks.begin(), ranks.end(), [](query_result a, query_result b)
		{
			return a.getScore() > b.getScore();
		});
		std::cout << "Your query was: " << buffer << std::endl;
		std::cout << "Results are:" << std::endl;

		std::cout << std::setw(maxLength) << std::left << "File Name " << " Rank " << std::endl;

		for (std::vector<query_result>::iterator i = ranks.begin(); i != ranks.end(); ++i)
		{
			std::cout << std::setw(maxLength) << std::left << i->getItem()->name() << " " << i->getScore() << std::endl;
		}
	}

	std::cout << "exiting....." << std::endl;

	return 0;
}