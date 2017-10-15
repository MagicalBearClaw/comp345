#include <string>
#include <vector>
#include <iostream>

#include "../includes/tokenizer.h"
#include "../includes/default_tokenizer_stratergy.h"

int main(void)
{
	tokenizer stripper = tokenizer(new default_tokenizer_stratergy());
    std::vector<std::string> tokens = stripper.tokenize("this, isn't a test. please! stop me(kidding). list of numbers: 1,2,3,4 and 5. here is a semi-colon;");

    for(auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}