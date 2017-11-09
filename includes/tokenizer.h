#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include "../includes/abstract_tokenizer_strategy.h"
#include "word_tokenizer_strategy.h"
#include <ostream>

/**
 * The class responsible of breaking up a string of words into tokens.
 * It does so by using a provided tokenizing strategy. if there is not 
 * a statergy that is provided, a default strategy will be used.
 * The tokenizer class is responsible of mangining the lifetime of a given strategy.
 * @see AbstractTokenizerStrategy
 * @see WordTokenizerStrategy
 * @see sentence_tokenzier_strategy
 */
class tokenizer
{
  public:
	/**
	* Allows to print debug information about the tokenizer instance.
	* @param out The ouput stream.
	* @param tokenizer The tokenizer instance.
	* @return std::ostream& operator the output stream.
	*/
	friend std::ostream &operator<<(std::ostream &out, const tokenizer &o);

	/**
	* @brief Copy constructor
	* Creates a new instance of tokenizer. 
	* @param strat The tokenizing strategy to use. if none specified, the
	* default strategy(word) will be used.
	* @see WordTokenizerStrategy
	*/
	tokenizer(AbstractTokenizerStrategy *strat = new WordTokenizerStrategy());
	/**
	* Deconstruct the tokenizer instance, freeing the strategy.
	*/
	~tokenizer();
	/**
	* Break up a string of words into a collection of tokens.
	* @param text The text to be tokenized.
	* @return std::vector<std::string> a collection of tokens.
	*/
	std::vector<std::string> tokenize(const std::string &text);
	/**
	* Allows to specify a new statergy to be used.
	* Note: The previous strategy will be freed.
	* @param strat The new strategy to be used to tokenize.
	*/
	void setTokenizerstrategy(AbstractTokenizerStrategy *strat);

  private:
	AbstractTokenizerStrategy *strategy;
};

#endif //TOKENIZER_H