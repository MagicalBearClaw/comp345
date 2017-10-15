#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include "../includes/I_tokenizer_stratergy.h"

/**
 * @brief This interface is responsible for providing a way to implement a new way
 * for breaking an input stream of characters into individual tokens.
 * 
 * 
 */
class tokenizer
{
public:
	std::vector<std::string> tokenize(const std::string& text);
	tokenizer(ITokenizerStratergy * strat);
	void setTokenizerStratergy(ITokenizerStratergy * strat);
	~tokenizer();
private:
    const std::string _delimeters;
	ITokenizerStratergy * stratergy;
};

#endif // TOKENIZER_H