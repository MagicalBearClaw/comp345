#ifndef TERM_INDEX_H
#define TERM_INDEX_H

#include <vector>
#include <map>
#include <string>

#include "../includes/stopword.h"

class TermIndex {
public:
  TermIndex();
  // ~TermIndex();

  void indexWord(std::string word);
  int operator[](const std::string word);
  double termWeight(std::string word, double documentModifier);
  void normalize(const std::vector<std::string> &word, const std::vector<double> &documentModifiers, StopWord *sw = nullptr);
  double docNorm();
private:
  double norm;
  std::map<std::string, int> termIndexer;
};

#endif
