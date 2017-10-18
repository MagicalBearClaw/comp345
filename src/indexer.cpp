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

// temporary to use string as stream

//int main()
//{
//	//An object idx of class indexer holds the data structures created from the input documents
//	//New creates object on stack and returns a pointer
//	Indexer *idx = new Indexer();
//	std::ifstream ifs("resources/index.txt");
//	assert(ifs.good() && "Invalid file name");
//	while (!ifs.eof())
//	{
//		ifs >> *idx;
//	}
//	std::cout << *idx;
//	std::cout << "done" << std::endl;
//	idx->normalize();
//	std::vector<query_result> ranks = idx->query("on top of each other to form a bigger project");
//	for (auto i = ranks.begin(); i != ranks.end(); i++) {
//		std::cout << i->getDocument().name() << i->getRank() << std::endl;
//	}
//
//	//Test this: Add an existing created document object  to the index object
//	//Document *d = new Document("filename");
//	//d >> idx;
//
//	return 0; //All went well.
//}

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

	return ifs;
}

void operator>>(Document &doc, Indexer &indexer)
{
	default_tokenizer_strategy * strat =  new default_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> v = tkzr.tokenize(doc.content());
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
	//std::vector<int> totals = calculatTotalWordCounts(words, indexer.documentIndex.size());
	//std::cout << "* " << std::left << std::setw(maxWordLength) << "total";
	//for (auto it = totals.begin(); it != totals.end(); ++it)
	//{
	//	std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
	//}
	//std::cout << " *" << std::endl;
	////display a hoirzontal line of asterisks
	//drawLine(horizontalLine);

	return ios;
}

int Indexer::size() {
	return documentCount;
	//return documentIndex.size();
}

int Indexer::calculateDocumentFrequency(std::string word){
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
	double dtModifier = 0.0; 
	
	for(auto iter = allWords.begin(); iter != allWords.end(); ++iter){
		
		documentFrequency = calculateDocumentFrequency(*iter);

		dtModifier = std::log((double)documentCount / (double)documentFrequency);
		docTermModifiers.push_back(dtModifier);
		docTermFrequency.push_back(documentFrequency);
	}
	for (auto iter = documentIndex.begin(); iter != documentIndex.end(); ++iter) {
		iter->normalize(allWords, docTermModifiers);
	}

	normalized = true;
}

bool Indexer::isNormalized(Indexer& indexer) {
	return normalized;
}

Document Indexer::operator[](int position)
{
	return documentIndex[position];
}


std::vector<query_result> Indexer::query(std::string queryString, int numOfResults) {

	std::vector<query_result> results;
	Document queryDoc;
	default_tokenizer_strategy * strat = new default_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> v = tkzr.tokenize(queryString);
	std::vector<std::string> commonWords;
	std::vector<double> commonDocTermModifiers;
	int position;
	for (auto i = v.begin(); i != v.end(); ++i) {
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
	for (auto iDoc = documentIndex.begin(); iDoc != documentIndex.end(); ++iDoc) {

		double vectorProductAcc = 0.0;
		for (auto cWord = commonWords.begin(); cWord != commonWords.end(); ++cWord) {
			position = cWord - commonWords.begin();
			commonModifier = commonDocTermModifiers[position];
			vectorProductAcc += ((iDoc->termWeight(*cWord, commonModifier)) * (queryDoc.termWeight(*cWord, commonModifier)));
		}
		score = vectorProductAcc / (iDoc->docNorm() * queryDoc.docNorm());
		if (std::isnan(score)) {
			score = 0;
		}
		results.push_back(query_result(*iDoc, score));
	}
	int reultCap = numOfResults;
	if (numOfResults > results.size())
		reultCap = results.size();

	results.erase(results.begin() + reultCap, results.end());
	return results;
}

//void removeStopWOrds(std::unordered_map<std::string, std::vector<int>>& words, std::string fileName)
//{
//	std::ifstream file(fileName.c_str());
//	std::string line;
//	if (!file.is_open())
//	{
//		std::cout << "Failed to open file: " << fileName << std::endl;
//		std::exit(-1);
//	}
//
//	while (std::getline(file, line))
//	{
//		words.erase(line);
//	}
//}

void calculateDocs(const std::vector<std::string>& docs, std::unordered_map<std::string, std::vector<int>>& processedWords)
{
	size_t current;
	std::string delimiters = " ,-':!().?\";—~{}/*\n";
	size_t next = -1;
	int index = 0;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		do
		{
			current = next + 1;
			std::string doc = *it;
			next = doc.find_first_of(delimiters, current);
			std::string currentword = doc.substr(current, next - current);
			std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
			if (currentword != "")
			{
				std::vector<int> counts = processedWords[currentword];
				counts[index] = counts[index] + 1;
				processedWords[currentword] = counts;
			}
		} while (next != std::string::npos);
		++index;
	}
}