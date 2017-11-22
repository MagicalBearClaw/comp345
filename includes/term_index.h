#ifndef TERM_INDEX_H
#define TERM_INDEX_H

#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>

#include "../includes/stopword.h"

class TermIndex {
public:
  TermIndex();
  // ~TermIndex();

  void indexWord(std::string& word);
  int operator[](const std::string& word);
  double termWeight(std::string& word, double documentModifier);
  void normalize(const std::vector<std::tuple<std::string, int, double>> &wftms, StopWord *sw = nullptr);
  double docNorm();
private:
  double norm;
  std::unordered_map<std::string, int> termIndexer;
};

#endif //TERM_INDEX_H
