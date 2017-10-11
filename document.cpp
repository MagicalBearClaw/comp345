// #include <document.h>
// // TODO complete the assignment
// // https://moodle.concordia.ca/moodle/pluginfile.php/2933888/mod_resource/content/1/a2.pdf

// //namespace
// Class Document
// {
//   private:

//   public:
//     Document(){

//     }

//     //operator<<


// };
#include "document.h"

const int notFound = 0;

Document::Document() 
  // : punctuations("_{}[]#()<>%:;.?*+^&|~!=,\"'\0")
 {} 

int Document::operator[](std::string word) {
  if (document.find(word) == document.end()) { // checks if word does not exist
    return 0;
  }
  return document[word];
}

void Document::indexWord(std::string word) {
  document[word] = (*this)[word] + 1;
}

// std::ifstream & operator>>(std::ifstream &ifs, Document &doc) {
 
//     // do file reading stuff for documents
//   }
// }
