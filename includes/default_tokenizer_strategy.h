#ifndef DEFAULT_TOKENIZER_strategy_H
#define DEFAULT_TOKENIZER_strategy_H

#include <string>
#include <vector>
#include "I_tokenizer_strategy.h"

/**
*  A default strategy to tokenize a string of words. 
*/

class default_tokenizer_strategy : public I_tokenizer_strategy
{
  public:
	/**
	* Create a new instance of a tokenizer strategy.
	* @param delimiters The set of delimiters to break up the string into tokens.
	* defaults to the set of punction characters.
	* i.e  ,\t-':!().?\";–—~{}/*\n\t\r
	*/
	default_tokenizer_strategy(const std::string &delimiters = " ,\t-':!().?\";–—~{}/*\n\t\r");

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

#endif