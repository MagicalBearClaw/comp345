#ifndef SENTENCE_H
#define SENTENCE_H

#include "Index_item.h"

class Sentence : public Index_item
{
    friend std::ostream& operator<<(std::ostream& stream, Sentence& sen);
public:
    Sentence();
    Sentence(std::string fileName);
    ~Sentence(); /**Destructor for Sentence class (does nothing so far)*/
    std::string content() const override;
    std::string name() const override;
    int size() const override;

    int getPos() const;
private:
    int pos; /** @brief Start position of the sentence(character offset) within document */
    std::string fileName;    /**The name of the sentence(document)*/
    std::string fileContent; /**The contents of the sentence(document)*/
    int _size;               /**The size of the sentence*/


};

#endif //SENTENCE_H