#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "..\includes\document.h"


const int notFound = 0;

Document::Document() {} 

Document::Document(std::string fileName): fileName(fileName) {
  std::fstream file(fileName);
  std::stringstream buffer;
  if (!file.is_open()) {
    std::cout << "Failed to open file: " << fileName << std::endl;
    std::_Exit(-1);
  }
  buffer << file.rdbuf();
  fileContent = buffer.str();
}

Document::~Document() {}

std::string Document::name() {
  return !fileName.empty() ? fileName : "unnamed document";
}


int Document::size() {
  return fileContent.length();
}

std::string Document::content() {
  return fileContent;
}

void Document::indexWord(std::string word) {
	dictionary[word] = (*this)[word] + 1;
}

int Document::operator[](std::string word) {
	if (dictionary.find(word) == dictionary.end()) { // checks if word does not exist
		return 0;
	}
	return dictionary[word];
}

std::vector<int> Document::getVector(const std::vector<std::string>& words, StopWord* sw = nullptr) {
	std::vector<int> wordCtr;
	// check if a stopword reference is given
	if (sw == nullptr) {
		for (auto i = words.begin(); i != words.end(); i++) {
				wordCtr.push_back((*this)[*i]);
		}
	}
	else 
	{
		for (auto i = words.begin(); i != words.end(); i++) {
			if (!sw->operator()(*i)) { // check that the current word *i is not a stopword before adding it to the vector
				wordCtr.push_back((*this)[*i]);
			}
		}
	}
	
	return wordCtr;
}