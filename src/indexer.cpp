// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
// https://moodle.concordia.ca/moodle/pluginfile.php/2933888/mod_resource/content/1/a2.pdf

#include "../includes/indexer.h"
#include "../includes/util.h"
#include "../includes/default_tokenizer_strategy.h"

//Remove unused included
//#include <algorithm>
//#include <map>
#include <assert.h>
#include <iostream>
//#include <istream>
//#include <vector>
#include <string>
//#include <sstream>
#include <fstream>
//#include <iterator>
//#include <ostream>
#include <iomanip>
//#include <cmath>


// temporary to use string as stream

int main()
{
	//An object idx of class indexer holds the data structures created from the input documents
	//New creates object on stack and returns a pointer
	Indexer *idx = new Indexer();
	std::ifstream ifs("resources/index.txt");
	assert(ifs.good() && "Invalid file name");
	while (!ifs.eof())
	{
		ifs >> *idx;
	}
	std::cout << *idx;
	std::cout << "done" << std::endl;
	
	std::vector<double> scores = idx->query("this is a test query?");

	//Test this: Add an existing created document object  to the index object
	//Document *d = new Document("filename");
	//d >> idx;

	return 0; //All went well.
}

Indexer::Indexer()
  : maxWordLength(0), documentCount(0), normalized(false)
{
	//documentIndex is intialized by an implicit call to vector<T> default constructor.
}

Indexer::~Indexer() {}

std::ifstream &operator>>(std::ifstream &ifs, Indexer &indexer)
{
	while (!ifs.eof()) {
		std::string docName = crawlToDelimiter(ifs, "\n");
		if (docName.empty()) {
			continue;
		}
		Document doc(docName);
		doc >> indexer; // "stream" document into indexer
	}
}

std::ifstream &operator>>(Document &doc, Indexer &indexer)
{
	default_tokenizer_strategy strat;
	std::vector<std::string> v = strat.tokenize(doc.content());
	for (auto i = v.begin(); i != v.end(); ++i) {
		if (std::find(indexer.allWords.begin(), indexer.allWords.end(), *i) == indexer.allWords.end()) {
			indexer.allWords.push_back(*i);
		}
		doc.indexWord(*i);
	}
	indexer.documentIndex.push_back(doc);
	indexer.docNames.push_back(doc.name());
	++indexer.documentCount;
	indexer.normalized = false;
}



std::ostream & operator<<(std::ostream &ios, Indexer &indexer) {
	int maxColumnLength = 10; // change this
	int maxWordLength = 20; // change this too
	std::string title = "dictionary"; // change this as well
	int columnCount = indexer.documentCount;
	int horizontalLine = (columnCount * (maxColumnLength + 2)) + (maxWordLength + 2) + columnCount + 2;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (auto it = indexer.documentIndex.begin(); it != indexer.documentIndex.end(); ++it)
	{
		std::cout << " * " << std::setw(maxColumnLength) << std::right << it->name();
	}
	std::cout << " *" << std::endl;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//main table display
	for (auto it = indexer.allWords.begin(); it != indexer.allWords.end(); ++it)
	{
		std::string currentWord = *it;
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		for (auto docs = indexer.documentIndex.begin(); docs != indexer.documentIndex.end(); ++docs)
		{
			std::cout << " * " << std::right << std::setw(maxColumnLength) << (*docs)[*it];
		}
		std::cout << " *" << std::endl;
	}

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	// Display totals
	//std::vector<int> totals = calculatTotalWordCounts(words, docs.size());
	//std::cout << "* " << std::left << std::setw(maxWordLength) << "total";
	//for (auto it = totals.begin(); it != totals.end(); ++it)
	//{
	//	std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
	//}
	//std::cout << " *" << std::endl;
	////display a hoirzontal line of asterisks
	//drawLine(horizontalLine);
}

int Indexer::size() {
	return documentCount;
	//return documentIndex.size();
}

int calculateDocumentFrequency(std::string word){
	int docFrequencyAcc = 0;
	for(auto iter = documentIndex.begin(); iter != documentIndex.end(); ++iter){
		docFrequencyAcc += (*iter)[word] ? 1 : 0;
	}

	return docFrequencyAcc;
}
// A function normalize() computes the tf-idf weights based on the number N of indexed documents.
void Indexer::normalize()
{
	int termFrequency = 0;
	int documentFrequency = 0;
	double dtModifier 0.0; 
	
	for(auto iter = allWords.begin(); iter != allWords.end(); ++iter){
		
		documentFrequency = calculateDocumentFrequency(*iter);

		dtModifier = log(documentCount / documentFrequency);
		docTermModifiers.push_back(dtModifier);
		docTermFrequency.push_back(documentFrequency);
	}
	for (auto iter = documentIndex.begin(); iter != documentIndex.end(); ++iter) {
		iter->normalize(allWords, docTermModifiers);
	}

	normalized = true;
}

bool isNormalized(Indexer& indexer){
	return normalized;
}

Document Indexer::operator[](int position)
{
	return documentIndex[position];
}


std::vector<double> query(std::string queryString) {
	Document queryDoc();
	default_tokenizer_strategy strat;
	std::vector<std::string> v = strat.tokenize(queryString);
	std::vector<std::string> commonWords;
	std::vector<double> commonDocTermModifiers;
	std::vector<double> scores;
	int position;
	for (auto i = v.begin(); i != v.end(); ++i) {
		if (std::find(indexer.allWords.begin(), indexer.allWords.end(), *i) != indexer.allWords.end()) {
			position = i - indexer.allWords.begin();
			queryDoc.indexWord(*i);
			commonWords.push_back(*i);
			commonDocTermModifiers.push_back(docTermModifiers[position]);
		}
	}
	queryDoc.normalize(allWords, docTermModifiers);
	double commonModifier;
	double vectorProductAcc = 0.0;
	for (auto iDoc = documentIndex.begin(); iDoc != documentIndex.end(); ++iDoc) {
		for (auto cWord = commonWords.begin(); cWord != commonWords.end(); ++cWord) {
			position = cWords - commonWords.begin();
			commonModifier = commonDocTermModifiers[position];
			vectorProductAcc += ((iDoc->termWeight(*word, commonModifier)) * (queryDoc.termWeight(*word, commonModifier));
		}
		scores.push_back(vectorProductAcc / (iDoc->docNorm() * queryDoc.docNorm()));
	}
	return scores;
}
