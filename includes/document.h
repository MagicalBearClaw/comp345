#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <map>
#include <vector>

#include "stopword.h"

#include "Index_item.h"

/**
 * Class used to store the contents of a file.
 * This class also can be used to fetch additional metadata about the 
 * file such as the name and the size (in characters) of the file.
 */
class Document : public Index_item {
  /**
   * Operator overload for debug output 
   * 
   * Outputs the file name, size, and content
   * 
   * @param stream The output stream to write to
   * @param doc the document to read from
   * 
   * @return std::ostream
   */
  friend std::ostream& operator<<(std::ostream& stream, Document& doc);
public:
  Document(); /**Constructor to create empty document*/
  /**
   * Constructor for creating a documet based on an existing file name.
   * 
   * This constructor will cause the application to terminate if it is given
   * a non existant file name.
   * 
   * @param fileName the name of the file the Document will be created from
   */
  Document(std::string fileName);
  ~Document(); /**Destructor for document class (does nothing so far)*/
  /**
   * Gets name of document
   * 
   * Gets the name of the file the document is based on what was input in the
   * constructor. If no parameter constructor is used the name will be "unnamed document"
   * 
   * @return std::string the name of the document
   */
  std::string name() const override;
  /**
   * Gets the size of the document
   * 
   * Gets the size of the contents of the document based on character count
   * 
   * @return int The number of characters in the document
   */
  int size() const override;
  /**
   * Gets the contents of the document
   * 
   * @return std::string the contents of the document
   */
  std::string content() const override;

private:
  std::string fileName;    /**The name of the document*/
  std::string fileContent; /**The contents of the document*/
  int _size;               /**The size of the document*/
};

#endif //DOCUMENT_H
