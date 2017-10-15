#include "..\includes\tokenizer.h"
#include "..\includes\util.h"

tokenizer::tokenizer(I_tokenizer_stratergy * strat) : stratergy(strat)
{
}

tokenizer::~tokenizer()
{
	SAFE_DELETE(stratergy)
}

std::vector<std::string> tokenizer::tokenize(const std::string& text) 
{
	if (text == "")
		return std::vector<std::string>();

	if(stratergy)
		return stratergy->tokenize(text);

	return std::vector<std::string>();
}

void tokenizer::setTokenizerStratergy(I_tokenizer_stratergy * strat)
{
	if (strat)
		SAFE_DELETE(stratergy)

	this->stratergy = strat;
}

std::ostream & operator<<(std::ostream & out, const tokenizer & o)
{
	if (o.stratergy)
		return out << "Current stratergy information: @0x" << o.stratergy << std::endl;

	return out << "Current stratergy information: There is not a statergy being used (nullptr)."  << std::endl;
}
