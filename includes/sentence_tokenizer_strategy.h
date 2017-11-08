#ifndef SENTENCE_TOKENIZER_STRATEGY_H
#define SENTENCE_TOKENIZER_STRATEGY_H

#include <string>
#include <vector>

#include "abstract_tokenizer_strategy.h"

class SentenceTokenizerStrategy : public abstract_tokenizer_strategy {
public:
  SentenceTokenizerStrategy(std::vector<std::string> abr, const std::string &delimiters = ".?!");
  virtual ~SentenceTokenizerStrategy();
  virtual std::vector<std::string> tokenize(const std::string &text);
private:
  std::vector<std::string> abreviations;
  std::string delimiters;
};

#endif //SENTENCE_TOKENIZER_STRATEGY_H