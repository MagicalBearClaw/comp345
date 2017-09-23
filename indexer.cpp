// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
#include <iostream>
#include <map>
#include <string>

int main() {
  std::map<std::string, int> dictionary;
  dictionary["test"] = 20;
  std::cout << dictionary["test"] << std::endl;
  return 0;
}
