#include "..\includes\tokenizer.h"
#include "..\includes\util.h"

tokenizer::tokenizer(I_tokenizer_strategy * strat) : strategy(strat)
{
}

tokenizer::~tokenizer()
{
	SAFE_DELETE(strategy)
}

std::vector<std::string> tokenizer::tokenize(const std::string& text) 
{
	if (text == "")
		return std::vector<std::string>();

	if(strategy)
		return strategy->tokenize(text);

	return std::vector<std::string>();
}

void tokenizer::setTokenizerstrategy(I_tokenizer_strategy * strat)
{
	if (strat)
		SAFE_DELETE(strategy)

	this->strategy = strat;
}

std::ostream & operator<<(std::ostream & out, const tokenizer & o)
{
	if (o.strategy)
		return out << "Current strategy information: @0x" << o.strategy << std::endl;

	return out << "Current strategy information: There is not a statergy being used (nullptr)."  << std::endl;
}
