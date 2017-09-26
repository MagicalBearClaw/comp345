// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
#include "indexer.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream> // temporary to use string as stream


typedef std::map<std::string, int> Worderator; // find better name


int main() {
  Worderator dictionary;
  std::string test = "this is a test of adding test words to the dictionary"; // replace by file IO
  std::istringstream testStream(test);
  std::string word;
  while (testStream >> word) {
    indexWord(dictionary, word);
  }
  std::cout << "test: " << dictionary["test"] << std::endl;
  std::cout << "dictionary: " << dictionary["dictionary"] << std::endl;
  std::cout << "this: " << dictionary["this"] << std::endl;
  return 0;
}

void indexWord(Worderator& dict, std::string& word) {
  if (dict.find(word) == dict.end()) { // checks if word does not exist
    dict[word] = 1;
  } else {
    dict[word]++;
  }
}