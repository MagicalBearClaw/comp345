#include "..\includes\sentence.h"
#include "../includes/util.h"

  Sentence::Sentence() {} 

  Sentence::Sentence(std::string fileName, std::string sentenceContent, int position): pos(position) {
    _content = sentenceContent;
    _name = fileName;
    _size = countWords(sentenceContent);
  }

  Sentence::~Sentence() {}
  // could be shared functionality
  int Sentence::size() const {
    return _size;
  }

  int Sentence::getPos() const {
      return pos;
  }
  
  