#ifndef INDEX_ITEM_H
#define INDEX_ITEM_H

#include <iostream>
#include <string>

/**
 * @brief This abstract base class(ABC) is used to define common code that is shared by all indexable items.
 * 
 */
class Index_item
{
  /**
   * @brief Extractor Operator overloaded used for debug output.
   * 
   * Derived classes that inherit from this base class should create their own version of this function.
   * 
   * @param ostream The output stream to write debug content to.
   * @param indexItem An object of type Index_item which will have its contents output to the ostream.
   * @return std::ostream& returns an output stream object in order to allow for function chainning.
   */
    friend std::ostream& operator<<(std::ostream& ostream, Index_item& indexItem);
  public:

    virtual std::string content() = 0;
    virtual std::string name() = 0;
    virtual int size() = 0;

    /**
     * @brief Deconstructor for all classes which implement this abstract base class.
     */
    virtual ~Index_item() {}
  private:
    std::string fileName;    /**The name of the index item*/
    std::string fileContent; /**The contents of the index item*/
    int _size; /**The size of the index item**/
};

#endif //INDEX_ITEM_H