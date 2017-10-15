#ifndef DEFAULT_TOKENIZER_STRATERGY_H
#define DEFAULT_TOKENIZER_STRATERGY_H

#include <string>
#include <vector>
#include "I_tokenizer_stratergy.h"


/**
* @brief This interface is responsible for providing a way to implement a new way
* for breaking an input stream of characters into individual tokens.
*
*
*/
class default_tokenizer_stratergy : public ITokenizerStratergy
{
public:
	default_tokenizer_stratergy(const std::string& delimiters = " ,\t-':!().?\";–~{}/*\n\t\r");
	virtual std::vector<std::string> tokenize(const std::string& text);

private:
	const std::string delimiters;

};

#endif