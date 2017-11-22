#ifndef TERM_INDEX_H
#define TERM_INDEX_H

#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>

#include "../includes/stopword.h"

/**
 * @brief A halfway class used to encapsulate the normalization function and some of it associated fomula parts.
 * 
 */
class TermIndex {
public:
  /**
   * @brief Default constructor
   * 
   * Initializes the norm to 0.0
   */
  TermIndex();
  // ~TermIndex();
  /**
   * @brief Add a word to the index
   * 
   * @param word 
   */
  void indexWord(std::string& word);

  /**
   * @brief Array accessor to retrieve content of index by word
   * 
   * @param word 
   * @return int 
   */
  int operator[](const std::string& word);
  /**
   * @brief The term weight associated between a word and document modifer
   * 
   * @param word 
   * @param documentModifier 
   * @return double 
   */
  double termWeight(std::string word, double documentModifier);
  /**
   * @brief The normalization function
   * 
   * @param wftms 
   * @param sw 
   */
  void normalize(const std::unordered_map<std::string, std::tuple<std::string, int, double>> &wftms, StopWord *sw = nullptr);
  double docNorm();
private:
  double norm;
  std::unordered_map<std::string, int> termIndexer;
};

#endif //TERM_INDEX_H
