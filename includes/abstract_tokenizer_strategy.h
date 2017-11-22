#ifndef ABSTRACT_TOKENIZER_STRATEGY_H
#define ABSTRACT_TOKENIZER_STRATEGY_H

#include <string>
#include <vector>

/**
 * This interface is responsible for providing a stategy to break text
 * into tokens.
 */
class AbstractTokenizerStrategy
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
	virtual ~AbstractTokenizerStrategy() {}
};

#endif //ABSTRACT_TOKENIZER_STRATEGY_H