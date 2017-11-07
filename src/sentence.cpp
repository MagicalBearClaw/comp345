#include "..\includes\sentence.h"
#include "../includes/util.h"

  Sentence::Sentence() {} 

  //TODO should there be just sentences in here? not document content
  Sentence::Sentence(std::string fileName): fileName(fileName) {
    // std::fstream file(fileName);
    // std::stringstream buffer;
    // if (!file.is_open()) {
    //   std::cout << "Failed to open file: " << fileName << std::endl;
    //   std::_Exit(-1);
    // }
    // buffer << file.rdbuf();
    // fileContent = buffer.str();
    // _size = fileContent.length();

    std::stringstream stream(strContent);
    _size = countWords(stream);
  }

  Sentence::~Sentence() {}
  
  int Sentence::size() const {
    return _size;
  }

  int Sentence::getPos() const {
      return pos;
  }
  
  