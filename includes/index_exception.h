#ifndef INDEX_EXCEPTION_H
#define INDEX_EXCEPTION_H

#include <exception>
#include <string>
/**
 * @brief A custom exception class for indexing related exceptions
 * 
 * Subclass of the std::exception
 * An IndexException is thrown when an action performed by an indexing class fails.
 * 
 */
class IndexException : public std::exception
{
public:

    /**
     * @brief provides an explanation of the exception
     * 
     * Will return the message associated with the exception
     * 
     * @return const char* the message contents of the exception
     */
  virtual const char* what() const noexcept override;
  /**
   * @brief Deconstructor
   * 
   */
  virtual ~IndexException() override;
private:
  // type is const char* to allow conversion from string constant
  static constexpr const char* msg = "Something went wrong while indexing data";
};

#endif
 
 
