#ifndef I_TOKENIZER_STRATERGY_H
#define I_TOKENIZER_STRATERGY_H

#include <string>
#include <vector>

/**
 * @brief This interface is responsible for providing a way to implement a new way
 * for breaking an input stream of characters into individual tokens.
 * 
 * 
 */
class ITokenizerStratergy
{
public:
    virtual std::vector<std::string> tokenize(const std::string& text) = 0;
	virtual ~ITokenizerStratergy() {}
};

#endif