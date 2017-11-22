#ifndef MOVIE_H
#define MOVIE_H

#include <map>
#include <vector>

#include "stopword.h"
#include "index_item.h"

/**
* @brief A Document is is used to store the contents of a fie.
* This class also can be used to fetch additional metadata about the
* file such as the name and the size (in characters) of the file.
* @see Index_item
*/
class Movie : public Index_item
{
	/**
	* Operator overload for debug output
	*
	* Outputs the file name, size, and content
	*
	* @param stream The output stream to write to
	* @param doc the document to read from
	*
	* @return std::ostream
	*/
	friend std::ostream &operator<<(std::ostream &stream, Movie &doc);

public:
	/**
	* @brief Constructor to create empty document
	*/
	Movie();
	/**
	* Overloaded constructor for creating a documet based on an existing file name.
	*
	* This constructor will cause the application to terminate if it is given
	* a non existant file name.
	*
	* @param fileName the name of the file the Document will be created from
	*/
	Movie(int id, const std::string& name, const std::string& content, const std::string& release_date);
	/**
	* @brief Destructor for document class (does nothing so far)
	*/
	~Movie();
	/**
	* Gets the size of the document
	*
	* Returns the size of the contents of the document based on character count.
	*
	* @return int The number of characters in the document
	*/
	int size() const override;

private:
	int _id;
	std::string _release_date;
};

#endif //MOVIE_H
