#ifndef SENTENCE_H
#define SENTENCE_H

#include "index_item.h"
/**
 * @brief A sentence is used to store the contents of a sentence.
 * This class can also be used to retrieve metadata such as size in words
 * of a sentence, or the filename of the document it was retrieved from.
 * Also keeps track of the sentences position in the document.
 * @see IndexItem
 */
class Sentence : public IndexItem
{
    /**
   * @brief Operator overload for debug output 
   * 
   * Outputs the file name, size, and content
   * 
   * @param stream The output stream to write to
   * @param sen the sentence to read from
   * 
   * @return std::ostream
   */
    friend std::ostream& operator<<(std::ostream& ostream, Sentence& sen);
public:
  /**
   * @brief Constructor to create empty sentence
   */
    Sentence();
  /**
   * Overloaded constructor for creating a sentence based on an existing string 
   * and position within a document.
   *.
   * @param sentenceContent the name of the file the Document will be created from\
   * @param position the offset position of the start of the sentence within the document
   */
    Sentence(std::string fileName, std::string sentenceContent, int position);
    /**
     * @brief Destructor for Sentence class (does nothing so far)
     */
    ~Sentence(); 
    /**
     * @brief Returns the word count of a sentence.
     *
     * Returns the size of a sentence which is the number of words within it. 
     *
     * @return int word count of the sentence
     */
    int size() const override;
    /**
     * @brief returs the start position (character offset) of the sentence
     * 
     * Start position is the character offset within a document of where the sentence is located.
     * 
     * @return int start positin of sentence
     */
    int getPos() const;
private:
    /** @brief Start position of the sentence(character offset) within document */
    int pos; 
};

#endif //SENTENCE_H