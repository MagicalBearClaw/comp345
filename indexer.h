#include <map>
#include <string>
#include <sstream>

#ifndef INDEXER_H
#define INDEXER_H

typedef std::map<std::string, int> Worderator; // find better name

int main();

void indexWord(Worderator& dict, std::string& word);

#endif
