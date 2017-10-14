#include <iostream>
#include "stopword.h"

int main() {
  StopWord s("sw.txt");
  std::cout << s("this") << s("is") << s("not") << s("a") << s("test") << std::endl;
  return 0;
}