#ifndef INDEX_EXCEPTION_H
#define INDEX_EXCEPTION_H

#include <exception>
#include <string>

class IndexException : public std::exception
{
public:
  virtual const char* what() const noexcept override;
  virtual ~IndexException() override;
private:
  // type is const char* to allow conversion from string constant
  static constexpr const char* msg = "Something went wrong indexing data";
};

#endif
