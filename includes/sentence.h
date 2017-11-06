#ifndef SENTENCE_H
#define SENTENCE_H

#include "../includes/Index_item.h"

class Sentence : Index_item
{
public:
    std::string content() override;
    std::string name() override;
    int size() override;

    int getPost();
private:
    /** @brief Start position of the sentence(character offset) within document */
    int pos;

};

#endif //SENTENCE_H