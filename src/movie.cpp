#include "../includes/movie.h"


std::ostream &operator<<(std::ostream &stream, Movie &movie)
{
	stream << "Movie: " << std::endl;
	stream << "Movie Name: " << movie.name() << std::endl;
	stream << "Size:(Character count of Movie summary) " << movie.size() << std::endl;
	stream << "Movie summary:\n"
		<< movie.content() << std::endl;
	return stream;
}



Movie::Movie()
{
}

Movie::Movie(int id, const std::string& name, const std::string& content, const std::string& release_date) : _id(id), _release_date(release_date)
{
	this->_content = content;
	this->_name = name;
}

Movie::~Movie()
{
}

int Movie::size() const
{
	return _content.length();
}