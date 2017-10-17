#include "../includes/document.h"
#include "../includes/default_tokenizer_strategy.h"

#include <iostream>
#include <string>

int main() {

	std::cout << "Please enter the words you wish to search for: " << std::endl;
	std::string userQuery;
	std::getline(std::cin, userQuery);

	default_tokenizer_strategy strat;
	//Should i pass by reference here?
	std::vector<std::string> tokenizedQuery = strat.tokenize(userQuery);
	
	//make use of query_result class here

	return 0; //All went well.
}