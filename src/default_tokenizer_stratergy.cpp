#include <algorithm>
#include "../includes/default_tokenizer_stratergy.h"

default_tokenizer_stratergy::default_tokenizer_stratergy(const std::string & delimiters) : delimiters(delimiters)
{
}


std::vector<std::string> default_tokenizer_stratergy::tokenize(const std::string & text)
{
	size_t current = 0;
	size_t next = -1;
	std::vector<std::string> words;
	do
	{
		current = next + 1;
		next = text.find_first_of(this->delimiters, current);
		std::string currentword = text.substr(current, next - current);
		std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
		if (currentword == "")
			continue;

		words.push_back(currentword);

	} while (next != std::string::npos);

	return words;
}