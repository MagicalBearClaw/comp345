#include "../includes/index_item.h"

std::ostream &operator<<(std::ostream &stream, IndexItem &indexItem)
{
  stream << "IndexItem: "<< std::endl;
  stream << "Name: " << indexItem.name() << std::endl;
  stream << "Size: " << indexItem.size() << std::endl;
  stream << "Content:\n"
         << indexItem.content() << std::endl;
  return stream;
}

std::string IndexItem::content() const
{
  return _content;
}

std::string IndexItem::name() const
{
  return !_name.empty() ? _name : "unnamed item";
}
