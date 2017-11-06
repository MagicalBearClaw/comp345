#include "../includes/indexer.h"
#include "../includes/util.h"
#include "../includes/default_tokenizer_strategy.h"
#include "../includes/tokenizer.h"


#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>


Indexer::Indexer()
  : maxWordLength(0), documentCount(0), normalized(false), maxColumnSize(18)
{}

Indexer::~Indexer() {}

std::ifstream &operator>>(std::ifstream &ifs, Indexer &indexer)
{
	while (!ifs.eof()) {
		std::string docName = crawlToDelimiter(ifs, "\n");
		if (docName.empty()) {
			continue;
		}
		if (indexer.maxColumnSize < docName.length()) {
			indexer.maxColumnSize = docName.length();
		}
		Document doc(docName);
		doc >> indexer; // "stream" document into indexer
	}

	return ifs;
}

void operator>>(Document &doc, Indexer &indexer)
{
	default_tokenizer_strategy * strat =  new default_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	TermIndex tIdx;
	std::vector<std::string> v = tkzr.tokenize(doc.content());
	for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i) {
		if (std::find(indexer.allWords.begin(), indexer.allWords.end(), *i) == indexer.allWords.end()) {
			if(i->length() > indexer.maxWordLength) {
				indexer.maxWordLength = i->length();
			}
			indexer.allWords.push_back(*i);
		}
		tIdx.indexWord(*i);
		// check if word count size is bigger than half the column
		if (std::to_string(tIdx[*i]).length() > indexer.maxColumnSize / 2 + indexer.maxColumnSize % 2 + 1) {
			indexer.maxColumnSize = std::to_string(tIdx[*i]).length() * 2 + 2;
		}
	}
	indexer.documents.push_back(doc);
	indexer.docNames.push_back(doc.name());
	indexer.documentIndices.push_back(tIdx);
	++indexer.documentCount;
	indexer.normalized = false;
}

std::ostream & operator<<(std::ostream &ios, Indexer &indexer) {
	if (!indexer.normalized) {
		indexer.normalize();
	}
	int maxColumnLength = indexer.maxColumnSize;
	int maxWordLength = indexer.maxWordLength;
	std::string title = "dictionary";
	int columnCount = indexer.documentCount;

	if (columnCount == 0)
		return ios;

	std::sort(indexer.docNames.begin(), indexer.docNames.end(), [](const std::string& a, const std::string& b)
	{
		return a.size() > b.size();
	});

	int horizontalLine = ((columnCount + 1) * (maxColumnLength + 2)) + (maxWordLength + 2) + columnCount + 3;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (std::vector<Document>::const_iterator it = indexer.documents.begin(); it != indexer.documents.end(); ++it)
	{
		std::cout << " * " << std::setw(maxColumnLength) << std::right << it->name();
	}
	std::cout << " * " << std::setw(maxColumnLength) << std::right << "Document Frequency";
	std::cout << " *" << std::endl;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	std::vector<int> totals;
	totals.resize(columnCount);

	//main table display
	for (std::vector<std::string>::const_iterator it = indexer.allWords.begin(); it != indexer.allWords.end(); ++it)
	{
		std::string currentWord = *it;
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		int indx = 0;
		int position = it - indexer.allWords.begin();
		double modifier = indexer.docTermModifiers[position];
		for (std::vector<TermIndex>::iterator docs = indexer.documentIndices.begin(); docs != indexer.documentIndices.end(); ++docs)
		{
			totals[indx] += (*docs)[*it];
			std::cout << " * " << std::right << std::setw(maxColumnLength / 2 - 1) << (*docs)[*it] << "|" << std::right << std::setw(maxColumnLength / 2 + maxColumnLength%2) << docs->termWeight(*it, modifier);
			++indx;
		}
		std::cout << " * " << std::right << std::setw(maxColumnLength) << indexer.docTermFrequency[position];
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


	std::cout << std::endl << "Without stopwords" << std::endl << std::endl;
	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (auto it = indexer.documents.begin(); it != indexer.documents.end(); ++it)
	{
		std::cout << " * " << std::setw(maxColumnLength) << std::right << it->name();
	}
	
	std::cout << " * " << std::setw(maxColumnLength) << std::right << "Document Frequency";
	std::cout << " *" << std::endl;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);
	totals.clear();
	totals.resize(columnCount);
	StopWord sw = StopWord("resources/stopwords.txt");

	//main table display
	for (auto it = indexer.allWords.begin(); it != indexer.allWords.end(); ++it)
	{
		if (sw(*it))
			continue;
		std::string currentWord = *it;
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		int indx = 0;
		int position = it - indexer.allWords.begin();
		double modifier = indexer.docTermModifiers[position];
		for (std::vector<TermIndex>::iterator docs = indexer.documentIndices.begin(); docs != indexer.documentIndices.end(); ++docs)
		{
			totals[indx] += (*docs)[*it];
			std::cout << " * " << std::right << std::setw(maxColumnLength / 2 - 1) << (*docs)[*it] << "|" << std::right << std::setw(maxColumnLength / 2 + maxColumnLength%2) << docs->termWeight(*it, modifier);
			++indx;
		}
		std::cout << " * " << std::right << std::setw(maxColumnLength) << indexer.docTermFrequency[position];
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

int Indexer::size() {
	return documentCount;
	//return documentIndex.size();
}

int Indexer::calculateDocumentFrequency(std::string word){
	int docFrequencyAcc = 0;
	for(std::vector<TermIndex>::iterator iter = documentIndices.begin(); iter != documentIndices.end(); ++iter){
		docFrequencyAcc += (*iter)[word] ? 1 : 0;
	}

	return docFrequencyAcc;
}
// A function normalize() computes the tf-idf weights based on the number N of indexed documents.
void Indexer::normalize()
{
	int termFrequency = 0;
	int documentFrequency = 0;
	double dtModifier = 0.0; 
	
	for(std::vector<std::string>::const_iterator iter = allWords.begin(); iter != allWords.end(); ++iter) {
		
		documentFrequency = calculateDocumentFrequency(*iter);

		dtModifier = std::log((double)documentCount / (double)documentFrequency);
		docTermModifiers.push_back(dtModifier);
		docTermFrequency.push_back(documentFrequency);
	}
	double weight;
	int maxAcc;
	for (std::vector<TermIndex>::iterator iter = documentIndices.begin(); iter != documentIndices.end(); ++iter) {
		iter->normalize(allWords, docTermModifiers);
		// verify that column size values are not suppased (this is for rendering the table later on)
		maxAcc = 0;
		for (auto word = allWords.begin(); word != allWords.end(); ++word) {
			maxAcc += (*iter)[*word];
			weight = iter->termWeight(*word, docTermModifiers[word - allWords.begin()]);
			if (std::to_string(weight).length() > maxColumnSize / 2 - maxColumnSize % 2) {
				maxColumnSize = std::to_string(weight).length() * 2 + 2;
			}
		}
		if (std::to_string(maxAcc).length() > maxColumnSize) {
			maxColumnSize = std::to_string(maxAcc).length();
		}
	}
	normalized = true;
}

bool Indexer::isNormalized(Indexer& indexer) {
	return normalized;
}

Document Indexer::operator[](int position)
{
	return documents[position];
}


std::vector<query_result> Indexer::query(std::string queryString, int numOfResults) {

	std::vector<query_result> results;
	TermIndex queryDoc;
	default_tokenizer_strategy * strat = new default_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> queryWords = tkzr.tokenize(queryString);
	std::vector<std::string> commonWords;
	std::vector<double> commonDocTermModifiers;
	int position;
	for (std::vector<std::string>::const_iterator i = queryWords.begin(); i != queryWords.end(); ++i) {
		auto element = std::find(allWords.begin(), allWords.end(), *i);
		if (element != allWords.end()) {
			position = element - allWords.begin();
			queryDoc.indexWord(*i);
			commonWords.push_back(*i);
			commonDocTermModifiers.push_back(docTermModifiers[position]);
		}
	}
	queryDoc.normalize(allWords, docTermModifiers);

	double commonModifier;
	double score;
	for (std::vector<TermIndex>::iterator iDoc = documentIndices.begin(); iDoc != documentIndices.end(); ++iDoc) {
		// get the document that matches the documentIndex position
		Document doc = documents[iDoc - documentIndices.begin()];
		double vectorProductAcc = 0.0;
		for (std::vector<std::string>::const_iterator cWord = commonWords.begin(); cWord != commonWords.end(); ++cWord) {
			position = cWord - commonWords.begin();
			commonModifier = commonDocTermModifiers[position];
			vectorProductAcc += ((iDoc->termWeight(*cWord, commonModifier)) * (queryDoc.termWeight(*cWord, commonModifier)));
		}
		score = vectorProductAcc / (iDoc->docNorm() * queryDoc.docNorm());
		if (std::isnan(score)) {
			score = 0;
		}
		results.push_back(query_result(doc, score));
	}
	int reultCap = numOfResults;
	if (numOfResults > results.size())
		reultCap = results.size();

	results.erase(results.begin() + reultCap, results.end());
	return results;
}


