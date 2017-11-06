#include <algorithm>
#include "../includes/default_tokenizer_strategy.h"

default_tokenizer_strategy::default_tokenizer_strategy(const std::string & delimiters) : delimiters(delimiters)
{
}


std::vector<std::string> default_tokenizer_strategy::tokenize(const std::string & text)
{
	size_t current = 0;
	size_t next = -1;
	std::vector<std::string> words;
	std::string currentsentence = "";
	do
	{
		current = next + 1;
		next = text.find_first_of(this->delimiters, current); // go until sentence terminating punctuation is reached
		currentsentence += text.substr(current, next - current);
		std::transform(currentsentence.begin(), currentsentence.end(), currentsentence.begin(), tolower);
		std::string lastWord = currentsentence.substr(currentsentence.find_last_of(" \t"), currentsentence.length - 1);
		if (std::find(abreviations.begin(), abreviations.end(), lastWord)) 
		
		if (currentsentence == "")
			continue;

		words.push_back(currentsentence);

	} while (next != std::string::npos);

	return words;
}