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
	: maxWordLength(0)
{

}

DocumentIndexer::~DocumentIndexer() 
{

}


std::ifstream &operator >> (std::ifstream &ifs, DocumentIndexer &indexer)
{
	while (!ifs.eof())
	{
		std::string docName = crawlToDelimiter(ifs, "\n");
		if (docName.empty())
		{
			continue;
		}
		if (indexer.maxColumnSize < docName.length());
		{
			indexer.maxColumnSize = docName.length();
		}
		Document *doc = new Document(docName); // probably memory leak make destructor for indexer clean this up
		*doc >> indexer; // "stream" document into indexer
	}

	return ifs;
}

void operator >> (Document &doc, DocumentIndexer &indexer)
{
	word_tokenizer_strategy * strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	TermIndex tIdx;
	std::vector<std::string> v = tkzr.tokenize(doc.content());
	for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i) {

		//find_if(table.begin(), table.end(), [&new_id](const entry &arg) { 
		//return arg.first == new_id; }) !=
		if (std::find_if(indexer.wftms.begin(), indexer.wftms.end(), [i](const DocumentIndexer::wordFrequencyTermMod &arg) { return std::get<0>(arg) == *i; }) == indexer.wftms.end()) {
			if (i->length() > indexer.maxWordLength) {
				indexer.maxWordLength = i->length();
			}
			indexer.wftms.push_back(make_tuple(*i, 0, 0)); // 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
														   // indexer.allWords.push_back(*i);
		}
		tIdx.indexWord(*i);
		// check if word count size is bigger than half the column
		if (std::to_string(tIdx[*i]).length() > indexer.maxColumnSize / 2 + indexer.maxColumnSize % 2 + 1) {
			indexer.maxColumnSize = std::to_string(tIdx[*i]).length() * 2 + 2;
		}
	}
	indexer.itis.push_back(std::make_tuple(&doc, tIdx)); // 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
														 // indexer.documents.push_back(doc);
	indexer.docNames.push_back(doc.name()); // remove me 😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠😠
											// indexer.documentIndices.push_back(tIdx);
	++indexer.documentCount;
	indexer.normalized = false;
}
// dont care for now
std::ostream & operator<<(std::ostream &ios, DocumentIndexer &indexer) {
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

	//TODO: why is this commented out?
	// std::cout << std::endl << "Without stopwords" << std::endl << std::endl;
	// //display a hoirzontal line of asterisks
	// drawLine(horizontalLine);

	// //display a header line including the word dictionary and the list of document names
	// std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	// //Loop to display all file names seperated by an asterisk
	// for (auto it = indexer.documents.begin(); it != indexer.documents.end(); ++it)
	// {
	// 	std::cout << " * " << std::setw(maxColumnLength) << std::right << it->name();
	// }

	// std::cout << " * " << std::setw(maxColumnLength) << std::right << "Document Frequency";
	// std::cout << " *" << std::endl;

	// //display a hoirzontal line of asterisks
	// drawLine(horizontalLine);
	// totals.clear();
	// totals.resize(columnCount);
	// StopWord sw = StopWord("resources/stopwords.txt");

	// //main table display
	// for (auto it = indexer.allWords.begin(); it != indexer.allWords.end(); ++it)
	// {
	// 	if (sw(*it))
	// 		continue;
	// 	std::string currentWord = *it;
	// 	std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
	// 	int indx = 0;
	// 	int position = std::distance(indexer.allWords.begin(), it);
	// 	double modifier = indexer.docTermModifiers[position];
	// 	for (std::vector<TermIndex>::iterator docs = indexer.documentIndices.begin(); docs != indexer.documentIndices.end(); ++docs)
	// 	{
	// 		totals[indx] += (*docs)[*it];
	// 		std::cout << " * " << std::right << std::setw(maxColumnLength / 2 - 1) << (*docs)[*it] << "|" << std::right << std::setw(maxColumnLength / 2 + maxColumnLength%2) << docs->termWeight(*it, modifier);
	// 		++indx;
	// 	}
	// 	std::cout << " * " << std::right << std::setw(maxColumnLength) << indexer.docTermFrequency[position];
	// 	std::cout << " *" << std::endl;
	// }
	// drawLine(horizontalLine);
	// // Display totals
	// std::cout << "* " << std::left << std::setw(maxWordLength) << "Total: ";
	// for (auto it = totals.begin(); it != totals.end(); ++it)
	// {
	// 	std::cout << " *1 " << std::right << std::setw(maxColumnLength) << *it;
	// }

	// std::cout << " * " << std::setw(maxColumnLength) << std::right << " ";
	// std::cout << " *" << std::endl;
	// drawLine(horizontalLine);
	return ios;
}
// same functionality, better name (term index frequency)
// int DocumentIndexer::calculateDocumentFrequency(std::string word) {
// 	int docFrequencyAcc = 0;
// 	for (std::vector<itemTermIndex>::iterator iter = itis.begin(); iter != itis.end(); ++iter) {
// 		docFrequencyAcc += std::get<1>(*iter)[word] ? 1 : 0;
// 	}

// 	return docFrequencyAcc;
// }

// A function normalize() computes the tf-idf weights based on the number N of indexed documents.
// can be implemented on base class
// void DocumentIndexer::normalize()
// {
// 	int termFrequency = 0;
// 	int documentFrequency = 0;
// 	double dtModifier = 0.0;

// 	for (std::vector<wordFrequencyTermMod>::iterator iter = wftms.begin(); iter != wftms.end(); ++iter) {

// 		documentFrequency = calculateDocumentFrequency(std::get<0>(*iter));

// 		dtModifier = std::log((double)documentCount / (double)documentFrequency);
// 		std::get<1>(*iter) = documentFrequency;
// 		std::get<2>(*iter) = dtModifier;
// 		// docTermModifiers.push_back(dtModifier);
// 		// docTermFrequency.push_back(documentFrequency);
// 	}
// 	double weight;
// 	int maxAcc;
// 	for (std::vector<itemTermIndex>::iterator iter = itis.begin(); iter != itis.end(); ++iter) {
// 		std::get<1>(*iter).normalize(wftms);
// 		// iter->normalize(allWords, docTermModifiers);
// 		// verify that column size values are not suppased (this is for rendering the table later on)
// 		maxAcc = 0;
// 		for (std::vector<wordFrequencyTermMod>::iterator word = wftms.begin(); word != wftms.end(); ++word) {
// 			maxAcc += std::get<1>(*iter)[std::get<0>(*word)];
// 			weight = std::get<1>(*iter).termWeight(std::get<0>(*word), std::get<2>(*word)); // iter->termWeight(*word, docTermModifiers[word - allWords.begin()]);
// 			if (std::to_string(weight).length() > maxColumnSize / 2 - maxColumnSize % 2) {
// 				maxColumnSize = std::to_string(weight).length() * 2 + 2;
// 			}
// 		}
// 		if (std::to_string(maxAcc).length() > maxColumnSize) {
// 			maxColumnSize = std::to_string(maxAcc).length();
// 		}
// 	}
// 	normalized = true;
// }

// override (pure virtual)
std::vector<query_result> DocumentIndexer::query(std::string queryString, int numOfResults) {

	std::vector<query_result> results;
	TermIndex queryDoc;
	word_tokenizer_strategy * strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> queryWords = tkzr.tokenize(queryString);
	std::vector<wordFrequencyTermMod> commonWords;
	// std::vector<double> commonDocTermModifiers;
	for (std::vector<std::string>::const_iterator i = queryWords.begin(); i != queryWords.end(); ++i) {
		std::vector<wordFrequencyTermMod>::iterator element = std::find_if(wftms.begin(), wftms.end(), [i](const wordFrequencyTermMod & arg) { return std::get<0>(arg) == *i; });
		if (element != wftms.end()) {
			queryDoc.indexWord(std::get<0>(*element));
			commonWords.push_back(*element);
											 // commonDocTermModifiers.push_back(docTermModifiers[position]);
		}
	}
	queryDoc.normalize(wftms);

	double commonModifier;
	double score;
	for (std::vector<itemTermIndex>::iterator iDoc = itis.begin(); iDoc != itis.end(); ++iDoc) {
		// get the document that matches the documentIndex position
		Document *doc = dynamic_cast<Document*>(std::get<0>(*iDoc));
		double vectorProductAcc = 0.0;
		for (std::vector<wordFrequencyTermMod>::iterator cWord = commonWords.begin(); cWord != commonWords.end(); ++cWord) {
			// position = cWord - commonWords.begin();
			commonModifier = std::get<2>(*cWord);
			vectorProductAcc += ((std::get<1>(*iDoc).termWeight(std::get<0>(*cWord), commonModifier)) * (queryDoc.termWeight(std::get<0>(*cWord), commonModifier)));
		}
		score = vectorProductAcc / (std::get<1>(*iDoc).docNorm() * queryDoc.docNorm());
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


