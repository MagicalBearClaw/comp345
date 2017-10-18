#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <ostream>
#include <map>
#include <vector>


#include "..\includes\stopword.h"

/**
 * Class used to store the contents of a file.
 * This class also can be used to fetch additional metadata about the 
 * file such as the name and the size (in characters) of the file.
 */
class Document {
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
  ~Document();/**Destructor for document class (does nothing so far)*/
  /**
   * Gets name of document
   * 
   * Gets the name of the file the document is based on what was input in the
   * constructor. If no parameter constructor is used the name will be "unnamed document"
   * 
   * @return std::string the name of the document
   */
  std::string name();
  /**
   * Gets the size of the document
   * 
   * Gets the size of the contents of the document based on character count
   * 
   * @return int The number of characters in the document
   */
  int size();
  double termWeight(std::string word, double documentModifier);
  
  double docNorm();
  
  void normalize(const std::vector<std::string>& words, const std::vector<double> documentModifiers, StopWord* sw = nullptr);
  /**
   * Gets the contents of the document
   * 
   * @return std::string the contents of the document
   */
  std::string content();
  void indexWord(std::string word);
  /**
   * Returns the word count for a specific word
   * 
   * @param word 
   * @return int 
   */
  int operator[](std::string word);
private:
  std::string fileName;/**The name of the document*/
  std::string fileContent;/**The contents of the document*/
  std::map<std::string, int> dictionary;
  double norm;
};

#endif
