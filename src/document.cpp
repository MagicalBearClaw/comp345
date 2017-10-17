#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

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

std::ostream operator<<(std::ostream& stream, Document& doc) {
  stream << "Document: " << doc.fileName << std::endl;
  stream << "Size: " << doc.size() << std::endl;
  stream << "Content:\n" << doc.fileContent << std::endl;
}

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

void Document::normalize(const std::vector<std::string>& words, const std::vector<double> documentModifiers, StopWord* sw) {
	double normAcc = 0.0;
	// check if a stopword reference is given
	if (sw == nullptr) {
		for (int i = 0; i != words.size(); ++i) {
			normAcc += pow(termWeight(words[i], documentModifiers[i]), 2);
		}
		
	}
	else 
	{
		for (int i = 0; i != words.size(); ++i) {
			if (!sw->operator()(words[i])) { // check that the current word *i is not a stopword before adding it to the vector
				normAcc += pow(termWeight(words[i], documentModifiers[i]), 2);
			}
		}
	}
	norm = std::sqrt(normAcc);
}

double Document::termWeight(std::string word, double documentFrequencyModifier) {
	int termCount = (*this)[word];
	return termCount ? (1 + log(termCount)) * documentFrequencyModifier : 0.0;
}

double Document::docNorm() {
	return norm;
}
