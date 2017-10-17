// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
// https://moodle.concordia.ca/moodle/pluginfile.php/2933888/mod_resource/content/1/a2.pdf
#include <algorithm>

#include "../includes/indexer.h"
#include "../includes/util.h"
#include "../includes/default_tokenizer_strategy.h"
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

}

Indexer::Indexer()
  : maxWordLength(0), documentCount(0)
{}

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
	indexer.documents.push_back(doc);
	indexer.docNames.push_back(doc.name());
	++indexer.documentCount;
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
	for (auto it = indexer.documents.begin(); it != indexer.documents.end(); ++it)
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
		for (auto docs = indexer.documents.begin(); docs != indexer.documents.end(); ++docs)
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
}

int Indexer::normalize()
{
	return 0;
}

Document Indexer::operator[](int position)
{
	return documents[position];
	//return nullptr;
}

double Indexer::calculateTFidf(double termFrequency, double documentFrequency)
{
	double tf_idf;

	tf_idf = (1 + log(termFrequency)* log(documentCount / documentFrequency));

	return tf_idf;
}
