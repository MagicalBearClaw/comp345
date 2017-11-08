#include "../includes/index_item.h"

std::ostream &operator<<(std::ostream &stream, Index_item &indexItem)
{
  stream << "Index_Item: "<< std::endl;
  stream << "Name: " << indexItem.name() << std::endl;
  stream << "Size: " << indexItem.size() << std::endl;
  stream << "Content:\n"
         << indexItem.content() << std::endl;
  return stream;
}

std::string Index_item::content() const
{
  return _content;
}

std::string Index_item::name() const
{
  return !_name.empty() ? _name : "unnamed item";
}
