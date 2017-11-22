#ifndef DOCUMENT_INDEXER_H
#define DOCUMENT_INDEXER_H

#include "indexer.h"
#include "Movie.h"
#include <unordered_map>

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
	*
	*/
	~MovieIndexer();

	// virtual int calculateDocumentFrequency(std::string term);
	/**
	* @brief the document frequency dft for a term t is defined as the number of documents that t appears in
	*
	* This member function is used to count the total number of documents that a word appears in
	* @param word the word to caluclate the frequency for
	* @return int the documentFrequency for the specified word
	*/
	// virtual int calculateDocumentFrequency(std::string term);

private:
	std::string getName(const std::string& summary, int id, int start);
	std::string getReleaseDate(const std::string& summary, int id, int start);
	std::unordered_map<int, std::string> MovieIndexer::buildMovieSummaryIndx(std::ifstream& ifsPlots);
	Movie* getMovieMetaInformationByName(const std::string& movieName);
	std::unordered_map<int, std::string> sumIndx;
	std::vector<Movie*> getMovies(const std::unordered_map<int, std::string>& sumIdx, std::ifstream& movieMetaInfo);
	std::vector<Movie*> movies;
};





#endif //DOCUMENT_INDEXER_H