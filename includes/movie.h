#ifndef MOVIE_H
#define MOVIE_H

#include <map>
#include <vector>

#include "stopword.h"
#include "index_item.h"

/**
* @brief A Movie is is used to store the contents of a movie.
* This class also can be used to fetch additional metadata about the
* movie such as the name size and release date.
* @see Index_item
*/
class Movie : public IndexItem
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
	* @brief Constructor to create empty Movie
	*/
	Movie();
	/**
	* Overloaded constructor for creating a movie based on its content
	*
	* @param id unique identifer for each movie
	* @param name the name of the movie
	* @param content the summary of the movie
	* @param release_date the release date of the movie
	*/
	Movie(int id, const std::string& name, const std::string& content, const std::string& release_date);
	/**
	* @brief Destructor for movie class (does nothing so far)
	*/
	~Movie();
	/**
	* Gets the size of the movie
	*
	* Returns the size of the summary of the movie
	*
	* @return int The number of characters in the movie description
	*/
	int size() const override;

private:
	int _id;
	std::string _release_date;
};

#endif //MOVIE_H
