#include "..\includes\tokenizer.h"
#include "..\includes\util.h"

tokenizer::tokenizer(ITokenizerStratergy * strat) : stratergy(strat)
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

void tokenizer::setTokenizerStratergy(ITokenizerStratergy * strat)
{
	if (strat)
		SAFE_DELETE(stratergy)

	this->stratergy = strat;
}
