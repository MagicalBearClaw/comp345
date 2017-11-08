#include <algorithm>
#include "../includes/word_tokenizer_strategy.h"

word_tokenizer_strategy::word_tokenizer_strategy(const std::string &delimiters) : delimiters(delimiters)
{
}

std::vector<std::string> word_tokenizer_strategy::tokenize(const std::string &text)
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