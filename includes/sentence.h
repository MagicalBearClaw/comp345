#ifndef SENTENCE_H
#define SENTENCE_H

#include "Index_item.h"

class Sentence : public Index_item
{
    friend std::ostream& operator<<(std::ostream& stream, Sentence& sen);
public:
    Sentence();
    Sentence(std::string fileName, std::string sentenceContent, int position);
    ~Sentence(); /**Destructor for Sentence class (does nothing so far)*/
    int size() const override;

    int getPos() const;
private:
    int pos; /** @brief Start position of the sentence(character offset) within document */
};

#endif //SENTENCE_H