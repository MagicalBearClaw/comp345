#include "..\includes\index_item.h"

//Move all the shared functionality (shared code) from document.cpp and sentence.cpp here
//remove repeated code in those classes

std::ostream& operator<<(std::ostream& stream, Index_item& indexItem) {
    stream << "Name: " << indexItem.name() << std::endl;
    stream << "Size: " << indexItem.size() << std::endl;
    stream << "Content:\n" << indexItem.content() << std::endl;
    return stream;
  }

std::string Index_item::content() const {
    return fileContent;
  }
  
  std::string Index_item::name() const {
    return !fileName.empty() ? fileName : "unnamed document";
  }