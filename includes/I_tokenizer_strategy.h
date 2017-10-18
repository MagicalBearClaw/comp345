#ifndef I_TOKENIZER_STATEGY_H
#define I_TOKENIZER_STATEGY_H

#include <string>
#include <vector>

/**
 * This interface is responsible for providing a statergy to break text
 * into tokens.
 */
class I_tokenizer_strategy
{
  public:
	/**
	* Break up a string of words into a collection of tokens.
	* @param text The text to be tokenized.
	* @return std::vector<std::string> a collection of tokens.
	*/
	virtual std::vector<std::string> tokenize(const std::string &text) = 0;
	/**
	 * @brief Deconstructor for all tokenizer strategies which implement this interface.
	 * 
	 */
	virtual ~I_tokenizer_strategy() {}
};

#endif