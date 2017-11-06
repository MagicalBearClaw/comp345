#ifndef SENTENCE_H
#define SENTENCE_H

//TODO not sure if this should be here or not?
#include "../includes/Index_item.h"

class Sentence : Index_item
{
public:
    std::string content() override { return "content";}
    std::string name() override {return "name";}
    int size() override { return 0;}

    int getPost() { return pos;}
private:
    /** @brief Start position of the sentence(character offset) within document */
    int pos;

};

#endif SENTENCE_H