#ifndef I_TOKENIZER_STRATERGY_H
#define I_TOKENIZER_STRATERGY_H

#include <string>
#include <vector>

/**
 * This interface is responsible for providing a statergy to break text
 * into tokens.
 */
class I_tokenizer_stratergy
{
public:
	/**
	* Break up a string of words into a collection of tokens.
	* @param text The text to be tokenized.
	* @return std::vector<std::string> a collection of tokens.
	*/
    virtual std::vector<std::string> tokenize(const std::string& text) = 0;
	virtual ~I_tokenizer_stratergy() {}
};

#endif