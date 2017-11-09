#ifndef WORD_TOKENIZER_STRATEGY_H
#define WORD_TOKENIZER_STRATEGY_H

#include <string>
#include <vector>
#include "abstract_tokenizer_strategy.h"

/**
 * @brief The default strategy to tokenize a string of words.
 * 
 * The tokenization method for spliting a string of words based on a sequence of delimiterd
 */
class WordTokenizerStrategy : public AbstractTokenizerStrategy
{
public:
	/**
		 * @brief constructor to create a new instance of a tokenizer strategy.
		 * @param delimiters The set of delimiters to break up the string into tokens.
		 * defaults to the set of punction characters seen below.
		 * i.e  ,\t-':!().?\";–—~{}/*\n\t\r
		 */
	WordTokenizerStrategy(const std::string &delimiters = " ,\t-':!().?\";–—~{}/*\n\t\r");

	/**
		* Breaks up a string into tokens.
		* @param text The text to be broken up into tokens.
		* @return std::vector<std::string> a collection of tokens.
		*/
	virtual std::vector<std::string> tokenize(const std::string &text);

private:
	/** Const member variable, only assigned in constructor*/
	const std::string delimiters;
};

#endif //WORD_TOKENIZER_STRATEGY_H