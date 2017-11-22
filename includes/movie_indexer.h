#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H

#include "indexer.h"
#include "Movie.h"
#include <unordered_map>

/**
 * @brief The MovieIndexer class is responsible for storing and maintaining a Movie index item.
 * 
 */
class MovieIndexer : public Indexer
{
	/**
	* @brief overloaded extractor to stream content from a file into an indexer object.
	*
	* @param ifs input file stream
	* @param indexer indexer object
	* @return std::ifstream allows for chaining
	*/
	friend std::ifstream &operator >> (std::ifstream &ifs, MovieIndexer &indexer);
	/**
	 * @brief Overloaded inserter used for deubug output
	 * 
	 * @param ios output stream of movie indexer class
	 * @param indexer the movieIndexer used for debug output
	 * @return std::ostream& 
	 */
	friend std::ostream & operator<<(std::ostream &ios, MovieIndexer &indexer);
	friend void operator >> (Movie &doc, MovieIndexer &indexer);
public:
	// virtual void normalize();
	virtual std::vector<query_result> query(std::string queryString, int numOfResults = 10);
	/**
	* @brief Default Constructor
	*
	*/
	MovieIndexer();
	/**
	* @brief Default Deconstructor
	* Iterates through all movie references and deletes them
	*/
	~MovieIndexer();

private:
	/**
	 * @brief Retrieves the movie name
	 * 
	 * @param summary 
	 * @param id 
	 * @param start 
	 * @return std::string 
	 */
	std::string getName(const std::string& summary, int id, int start);
	/**
	 * @brief Retrieves the movie release date
	 * 
	 * @param summary 
	 * @param id 
	 * @param start 
	 * @return std::string 
	 */
	std::string getReleaseDate(const std::string& summary, int id, int start);
	/**
	 * @brief Produce the movie summary index
	 * 
	 * @param ifsPlots 
	 * @return std::unordered_map<int, std::string> 
	 */
	std::unordered_map<int, std::string> buildMovieSummaryIndx(std::ifstream& ifsPlots);
	/**
	 * @brief given a movie name retrieve its meta information
	 * 
	 * @param movieName 
	 * @return Movie* 
	 */
	Movie* getMovieMetaInformationByName(const std::string& movieName);
	std::unordered_map<int, std::string> sumIndx;
	std::vector<Movie*> getMovies(const std::unordered_map<int, std::string>& sumIdx, std::ifstream& movieMetaInfo);
	std::vector<Movie*> movies;
};

#endif //DOCUMENT_INDEXER_H