#include "../includes/sentence.h"
#include "../includes/util.h"

std::ostream &operator<<(std::ostream &stream, Sentence &sentence)
{
  stream << "Sentence: "<< std::endl;
  stream << "Name: " << sentence.name() << std::endl;
  stream << "Size: (Number of Words in sentence) " << sentence.size() << std::endl;
  stream << "Content:\n"
         << sentence.content() << std::endl;
  return stream;
}
  Sentence::Sentence() {} 

  Sentence::Sentence(std::string fileName, std::string sentenceContent, int position): pos(position) {
    _content = sentenceContent;
    _name = fileName;
    _size = countWords(sentenceContent);
  }

  Sentence::~Sentence() {}
  
  //Size represents different values, but method for returning size is same as sibling class.
  int Sentence::size() const {
    return _size;
  }

  int Sentence::getPos() const {
      return pos;
  }
  
  