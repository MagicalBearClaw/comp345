#ifndef INDEX_ITEM_H
#define INDEX_ITEM_H

#include <iostream>
#include <string>
#include <fstream>

/**
 * @brief This abstract base class(ABC) is used to define common code that is shared by all indexable items.
 * 
 */
class IndexItem
{
  /**
   * @brief Extractor Operator overloaded used for debug output.
   * 
   * Derived classes that inherit from this base class should create their own version of this function.
   * 
   * @param ostream The output stream to write debug content to.
   * @param indexItem An object of type IndexItem which will have its contents output to the ostream.
   * @return std::ostream& returns an output stream object in order to allow for function chainning.
   */
  friend std::ostream &operator<<(std::ostream &ostream, IndexItem &indexItem);

public:
  /**
     * @brief Returns the content for an index item.
     * 
     * @return std::string the content of index item
     */
  virtual std::string content() const;
  /**
     * @brief Returns the name of an index item
     * 
     * @return std::string the name of index item
     */
  virtual std::string name() const;
  /**
     * @brief Returns the size of an index item
     * 
     * @return int size of item
     */
  virtual int size() const = 0;
  /**
     * @brief Deconstructor for all classes which implement this abstract base class.
     */
  virtual ~IndexItem() {}

protected:
  std::string _name;    /**The name of the index item*/
  std::string _content; /**The contents of the index item*/
  int _size;            /**The size of the index item*/
};

#endif //INDEX_ITEM_H