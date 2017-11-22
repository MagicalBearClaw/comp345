#include "../includes/indexer.h"
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "../includes/movie_indexer.h"
#include "../includes/index_exception.h"

int main()
{
	int numOfResults = 6; // in case query is in result
	Indexer *idx = new MovieIndexer();
	std::ifstream ifs("resources/movie_indexer.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *(MovieIndexer*)idx;
	}
	ifs.close();
	idx->normalize(); // normalize before accepting queries
	std::string buffer = "";
	while (true)
	{
		buffer.clear();
		std::cout << "\nPlease enter a movie name so we can give you more recomendations based on your likings.." << std::endl;
 		std::getline(std::cin, buffer);
		if (buffer.empty())
			continue;
		else if (buffer == "!q")
			break;

		std::vector<query_result> ranks;
		try{
			 ranks = idx->query(buffer, numOfResults);
		}
		catch (const IndexException &e){
			std::cerr << e.what() << std::endl;
			std::cout << "No movie with that name was found" << std::endl;
			continue;
		}
		
		int maxLength = ranks[0].getItem()->name().size();
		std::sort(ranks.begin(), ranks.end(), [](query_result a, query_result b)
		{
			return a.getScore() > b.getScore();
		});
		std::cout << "Your query was: " << buffer << std::endl;
		std::cout << "Results are:\n=============================" << std::endl;

		for (int i = 0; i != ranks.size(); ++i)
		{
			std::string name =  ranks[i].getItem()->name();
			if(name != buffer) {
				std::cout << std::setw(maxLength) << std::left << name << std::endl;
			}
		}
	}

	std::cout << "exiting....." << std::endl;

	return 0;
}