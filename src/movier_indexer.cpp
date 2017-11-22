﻿#include "../includes/movie_indexer.h"
#include "../includes/util.h"
#include "../includes/word_tokenizer_strategy.h"
#include "../includes/tokenizer.h"
#include "../includes/movie.h"
#include "../includes/index_item.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <sstream>

MovieIndexer::MovieIndexer()
{
}

MovieIndexer::~MovieIndexer()
{
	for (std::vector<Movie*>::const_iterator it = movies.begin(); it != movies.end(); ++it)
	{
		if (*it)
		{
			delete (*it);
		}
	}

}
std::ifstream &operator >> (std::ifstream &ifs, MovieIndexer &indexer)
{
	std::string metaDetaDoc;
	std::string summariesDoc;
	std::string lines[2];
	int i = 0;
	while (!ifs.eof())
	{
		lines[i] = crawlToDelimiter(ifs, "\n");
		++i;
	}
	metaDetaDoc = lines[0];
	summariesDoc = lines[1];
	
	std::ifstream ifsMeta(metaDetaDoc);
	assert(ifsMeta.good() && "Invalid file name");

	std::ifstream ifsPlots(summariesDoc);
	assert(ifsPlots.good() && "Invalid file name");

	indexer.sumIndx;
	indexer.sumIndx = indexer.buildMovieSummaryIndx(ifsPlots);
	ifsPlots.close();

	indexer.movies = indexer.getMovies(indexer.sumIndx, ifsMeta);

	for (std::vector<Movie*>::const_iterator it = indexer.movies.begin(); it != indexer.movies.end(); ++it)
	{
		if (*it)
		{
			*(*it) >> indexer;
		}
	}

	ifsMeta.close();
	return ifs;
}

void operator >> (Movie &movie, MovieIndexer &indexer)
{
	word_tokenizer_strategy *strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	TermIndex tIdx;
	std::vector<std::string> v = tkzr.tokenize(movie.content());
	for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i)
	{

		//find_if(table.begin(), table.end(), [&new_id](const entry &arg) {
		//return arg.first == new_id; }) !=
		if (std::find_if(indexer.wftms.begin(), indexer.wftms.end(), [i](const MovieIndexer::wordFrequencyTermMod &arg) { return std::get<0>(arg) == *i; }) == indexer.wftms.end())
		{
			if (i->length() > indexer.maxWordLength)
			{
				indexer.maxWordLength = i->length();
			}
			indexer.wftms.push_back(make_tuple(*i, 0, 0)); // 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
		}
		std::string w = *i;
		tIdx.indexWord(w);
		// check if word count size is bigger than half the column
		if (std::to_string(tIdx[*i]).length() > indexer.maxColumnSize / 2 + indexer.maxColumnSize % 2 + 1)
		{
			indexer.maxColumnSize = std::to_string(tIdx[*i]).length() * 2 + 2;
		}
	}
	indexer.itis.push_back(std::make_tuple(&movie, tIdx)); // 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
	indexer.docNames.push_back(movie.name());
	++indexer.documentCount;
	indexer.normalized = false;
}

std::ostream &operator<<(std::ostream &ios, MovieIndexer &indexer)
{
	// return debug info
	return ios;
}

std::vector<query_result> MovieIndexer::query(std::string queryString, int numOfResults)
{

	Movie* movie = this->getMovieMetaInformationByName(queryString);

	if (!normalized)
	{
		normalize();
	}
	std::vector<query_result> results;
	TermIndex queryDoc;
	word_tokenizer_strategy *strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> queryWords = tkzr.tokenize(movie->content());
	std::vector<wordFrequencyTermMod> commonWords;
	// std::vector<double> commonDocTermModifiers;
	for (std::vector<std::string>::const_iterator i = queryWords.begin(); i != queryWords.end(); ++i)
	{
		std::vector<wordFrequencyTermMod>::iterator element = std::find_if(wftms.begin(), wftms.end(), [i](const wordFrequencyTermMod &arg) { return std::get<0>(arg) == *i; });
		if (element != wftms.end())
		{
			queryDoc.indexWord(std::get<0>(*element));
			commonWords.push_back(*element);
			// commonDocTermModifiers.push_back(docTermModifiers[position]);
		}
	}
	queryDoc.normalize(wftms);

	double commonModifier;
	double score;
	for (std::vector<itemTermIndex>::iterator iDoc = itis.begin(); iDoc != itis.end(); ++iDoc)
	{
		// get the document that matches the documentIndex position
		Movie *movie = dynamic_cast<Movie *>(std::get<0>(*iDoc));
		double vectorProductAcc = 0.0;
		for (std::vector<wordFrequencyTermMod>::iterator cWord = commonWords.begin(); cWord != commonWords.end(); ++cWord)
		{
			// position = cWord - commonWords.begin();
			commonModifier = std::get<2>(*cWord);
			vectorProductAcc += ((std::get<1>(*iDoc).termWeight(std::get<0>(*cWord), commonModifier)) * (queryDoc.termWeight(std::get<0>(*cWord), commonModifier)));
		}
		score = vectorProductAcc / (std::get<1>(*iDoc).docNorm() * queryDoc.docNorm());
		if (std::isnan(score))
		{
			score = 0;
		}
		results.push_back(query_result(movie, score));
	}
	int reultCap = numOfResults + 1;
	if (numOfResults > results.size())
		reultCap = results.size();
	std::sort(results.begin(), results.end(), [](query_result a, query_result b) { return a.getScore() > b.getScore(); });
	results.erase(results.begin() + reultCap, results.end());
	results.erase(results.begin(), results.begin() + 1);
	return results;
}

std::string MovieIndexer::getName(const std::string& summary, int id, int start)
{

	int current = start;
	int next = 0;
	int i = 0;
	std::string moviewName;
	int prev = 0;
	while (i < 3)
	{

		next = summary.find_first_of('\t', current);
		prev = current;
		current = next + 1;
		++i;
	}
	moviewName = summary.substr(prev, next - prev);

	return moviewName;
}


std::unordered_map<int, std::string> MovieIndexer::buildMovieSummaryIndx(std::ifstream& ifsPlots)
{
	int sepPos = 0;
	std::unordered_map<int, std::string> sumIndx;
	std::string id = "";
	std::string summary = "";
	while (!ifsPlots.eof())
	{
		std::string line;
		std::getline(ifsPlots, line);
		sepPos = line.find_first_of('\t', 0);
		id = line.substr(0, sepPos);
		summary = line.substr(sepPos+ 1);
		sumIndx.emplace(std::atoi(id.c_str()), summary);
	}

	return sumIndx;
}

Movie* MovieIndexer::getMovieMetaInformationByName(const std::string& movieName)
{
	// cant use iterator here, cause of it trying to create an instance of an abstract base class.
	for (int i = 0; i < itis.size(); i++)
	{
		Movie *movie = dynamic_cast<Movie *>(std::get<0>(itis[i]));
		if (movie->name() == movieName)
			return movie;
	}

	return nullptr;
}

std::string MovieIndexer::getReleaseDate(const std::string& summary, int id, int start)
{
	int current = start;
	int next = 0;
	int i = 0;
	std::string releaseDate;
	int prev = 0;
	while (i < 4)
	{

		next = summary.find_first_of('\t', current);
		prev = current;
		current = next + 1;
		++i;
	}
	releaseDate = summary.substr(prev, next - prev);

	return releaseDate;
}


std::vector<Movie*> MovieIndexer::getMovies(const std::unordered_map<int, std::string>& sumIdx, std::ifstream& movieMetaInfo)
{

	std::vector<Movie*> movies;
	std::vector<int> ids;
	std::vector<std::string> releaseDates;
	std::vector<std::string> names;

	int current = 0;
	int prev = 0;
	int next = 0;
	std::string id = "";
	std::string releaseDate = "";
	std::string name = "";

	while (!movieMetaInfo.eof())
	{
		std::string line;
		std::getline(movieMetaInfo, line);

		next = line.find_first_of('\t', current);
		id = line.substr(0, next);
		ids.push_back(std::atoi(id.c_str()));
		current = next + 1;

		// skip 1 tab because information is not used
		next = line.find_first_of('\t', current);
		current = next + 1;
		next = line.find_first_of('\t', current);
		prev = current;
		current = next + 1;

		name = line.substr(prev, next - prev);
		names.push_back(name);
		next = line.find_first_of('\t', current);
		prev = current;
		current = next + 1;
		releaseDate = line.substr(prev, next-prev);
		releaseDates.push_back(releaseDate);
		current = 0;
		prev = 0;
		next = 0;
	}

	for ( auto it = sumIdx.begin(); it != sumIdx.end(); ++it)
	{
		int current = (*it).first;
		std::string summary = (*it).second;
		for (int i = 0; i < ids.size(); i++)
		{
			if (ids[i] == current)
			{
				Movie * movie = new Movie(current, names[i], summary, releaseDates[i]);
				movies.push_back(movie);
			}
		}

	}

	return movies;
}

