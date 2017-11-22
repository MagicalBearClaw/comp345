#include "../includes/document_indexer.h"
#include "../includes/util.h"
#include "../includes/word_tokenizer_strategy.h"
#include "../includes/tokenizer.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <iterator>

DocumentIndexer::DocumentIndexer()
{
	maxWordLength = 0;
}

DocumentIndexer::~DocumentIndexer()
{
}

std::ifstream &operator>>(std::ifstream &ifs, DocumentIndexer &indexer)
{
	while (!ifs.eof())
	{
		std::string docName = crawlToDelimiter(ifs, "\n");
		if (docName.empty())
		{
			continue;
		}
		if (indexer.maxColumnSize < docName.length())
			;
		{
			indexer.maxColumnSize = docName.length();
		}
		Document *doc = new Document(); // probably memory leak make destructor for indexer clean this up
		*doc >> indexer;											 // "stream" document into indexer
	}

	return ifs;
}

void operator>>(Document &doc, DocumentIndexer &indexer)
{
	word_tokenizer_strategy *strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	TermIndex tIdx;
	std::vector<std::string> v = tkzr.tokenize(doc.content());
	for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i)
	{

		//find_if(table.begin(), table.end(), [&new_id](const entry &arg) {
		//return arg.first == new_id; }) !=
		if (std::find_if(indexer.wftms.begin(), indexer.wftms.end(), [i](const DocumentIndexer::wordFrequencyTermMod &arg) { return std::get<0>(arg) == *i; }) == indexer.wftms.end())
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
	indexer.itis.push_back(std::make_tuple(&doc, tIdx)); // 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
	indexer.docNames.push_back(doc.name());
	++indexer.documentCount;
	indexer.normalized = false;
}

std::ostream &operator<<(std::ostream &ios, DocumentIndexer &indexer)
{
	if (!indexer.normalized)
	{
		indexer.normalize();
	}
	int maxColumnLength = indexer.maxColumnSize;
	int maxWordLength = indexer.maxWordLength;
	std::string title = "dictionary";
	int columnCount = indexer.documentCount;

	if (columnCount == 0)
		return ios;

	std::sort(indexer.docNames.begin(), indexer.docNames.end(), [](const std::string &a, const std::string &b) {
		return a.size() > b.size();
	});

	int horizontalLine = ((columnCount + 1) * (maxColumnLength + 2)) + (maxWordLength + 2) + columnCount + 3;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (std::vector<std::string>::const_iterator it = indexer.docNames.begin(); it != indexer.docNames.end(); ++it)
	{
		std::cout << " * " << std::setw(maxColumnLength) << std::right << *it;
	}
	std::cout << " * " << std::setw(maxColumnLength) << std::right << "Document Frequency";
	std::cout << " *" << std::endl;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	std::vector<int> totals;
	totals.resize(columnCount);

	//main table display
	for (std::vector<DocumentIndexer::wordFrequencyTermMod>::iterator it = indexer.wftms.begin(); it != indexer.wftms.end(); ++it)
	{
		std::string currentWord = std::get<0>(*it);
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		int indx = 0;
		// int position = std::distance(indexer.allWords.begin(), it);
		double modifier = std::get<2>(*it);
		for (std::vector<Indexer::itemTermIndex>::iterator docs = indexer.itis.begin(); docs != indexer.itis.end(); ++docs)
		{
			totals[indx] += std::get<1>(*docs)[currentWord];
			std::cout << " * " << std::right << std::setw(maxColumnLength / 2 - 1) << std::get<1>(*docs)[currentWord] << "|" << std::right << std::setw(maxColumnLength / 2 + maxColumnLength % 2) << std::get<1>(*docs).termWeight(currentWord, std::get<2>(*it));
			++indx;
		}
		std::cout << " * " << std::right << std::setw(maxColumnLength) << std::get<1>(*it);
		std::cout << " *" << std::endl;
	}
	drawLine(horizontalLine);
	// Display totals
	std::cout << "* " << std::left << std::setw(maxWordLength) << "Total: ";
	for (auto it = totals.begin(); it != totals.end(); ++it)
	{
		std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
	}

	std::cout << " * " << std::setw(maxColumnLength) << std::right << " ";
	std::cout << " *" << std::endl;
	drawLine(horizontalLine);

	std::cout << "Without stopwords" << std::endl;

	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (std::vector<std::string>::const_iterator it = indexer.docNames.begin(); it != indexer.docNames.end(); ++it)
	{
		std::cout << " * " << std::setw(maxColumnLength) << std::right << *it;
	}
	std::cout << " * " << std::setw(maxColumnLength) << std::right << "Document Frequency";
	std::cout << " *" << std::endl;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	totals = {};
	totals.resize(columnCount);

	StopWord sw = StopWord("resources/stopwords.txt");
	//main table display
	for (std::vector<DocumentIndexer::wordFrequencyTermMod>::iterator it = indexer.wftms.begin(); it != indexer.wftms.end(); ++it)
	{
		if (sw(std::get<0>(*it)))
		{
			continue;
		}
		std::string currentWord = std::get<0>(*it);
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		int indx = 0;
		// int position = std::distance(indexer.allWords.begin(), it);
		double modifier = std::get<2>(*it);
		for (std::vector<Indexer::itemTermIndex>::iterator docs = indexer.itis.begin(); docs != indexer.itis.end(); ++docs)
		{
			totals[indx] += std::get<1>(*docs)[currentWord];
			std::cout << " * " << std::right << std::setw(maxColumnLength / 2 - 1) << std::get<1>(*docs)[currentWord] << "|" << std::right << std::setw(maxColumnLength / 2 + maxColumnLength % 2) << std::get<1>(*docs).termWeight(currentWord, std::get<2>(*it));
			++indx;
		}
		std::cout << " * " << std::right << std::setw(maxColumnLength) << std::get<1>(*it);
		std::cout << " *" << std::endl;
	}
	drawLine(horizontalLine);
	// Display totals
	std::cout << "* " << std::left << std::setw(maxWordLength) << "Total: ";
	for (auto it = totals.begin(); it != totals.end(); ++it)
	{
		std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
	}

	std::cout << " * " << std::setw(maxColumnLength) << std::right << " ";
	std::cout << " *" << std::endl;
	drawLine(horizontalLine);

	
	return ios;
}

std::vector<query_result> DocumentIndexer::query(std::string queryString, int numOfResults)
{
	if (!normalized)
	{
		normalize();
	}
	std::vector<query_result> results;
	TermIndex queryDoc;
	word_tokenizer_strategy *strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> queryWords = tkzr.tokenize(queryString);
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
		Document *doc = dynamic_cast<Document *>(std::get<0>(*iDoc));
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
		results.push_back(query_result(doc, score));
	}
	int reultCap = numOfResults;
	if (numOfResults > results.size())
		reultCap = results.size();
	std::sort(results.begin(), results.end(), [](query_result a, query_result b) { return a.getScore() > b.getScore(); });
	results.erase(results.begin() + reultCap, results.end());
	return results;
}
