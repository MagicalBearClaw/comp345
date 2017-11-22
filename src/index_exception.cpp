#include "..\includes\index_exception.h"

const char* IndexException::what() const noexcept {
  return msg;
}

IndexException::~IndexException() {}
