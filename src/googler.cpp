//#include "../includes/indexer.h"
//#include <fstream>
//#include <assert.h>
//#include <iostream>
//#include <algorithm>
//#include <iomanip>
//int main()
//{
//	int numOfResults = 10;
//	Indexer *idx = new Indexer();
//	std::ifstream ifs("resources/index.txt");
//	assert(ifs.good() && "Invalid file name");
//	while (!ifs.eof())
//	{
//		ifs >> *idx;
//	}
//
//	std::string buffer = "";
//	while (true)
//	{
//		buffer.clear();
//		std::cout << "Please enter your query or type !q to quit." << std::endl;
//		std::getline(std::cin, buffer);
//		if (buffer.empty())
//			continue;
//		else if (buffer == "!q")
//			break;
//		
//		idx->normalize();
//		std::vector<query_result> ranks = idx->query(buffer, numOfResults);
//		std::sort(ranks.begin(), ranks.end(), [](query_result a, query_result b) 
//		{
//			return a.getDocument().name().size() > b.getDocument().name().size();
//		});
//		int maxLength = ranks[0].getDocument().name().size();
//		std::sort(ranks.begin(), ranks.end(), [](query_result a, query_result b)
//		{
//			return a.getRank() > b.getRank();
//		});
//		std::cout << "Your query was: " << buffer << std::endl;
//		std::cout << "Results are:" << std::endl;
//
//		std::cout << std::setw(maxLength) << std::left  << "File Name " << " Rank "<< std::endl;
//
//		for (auto i = ranks.begin(); i != ranks.end(); ++i)
//		{
//			std::cout << std::setw(maxLength) << std::left << i->getDocument().name() << i->getRank() << std::endl;
//		}
//	} 
//
//	std::cout << "exiting....." << std::endl;
//
//	return 0; 
//}