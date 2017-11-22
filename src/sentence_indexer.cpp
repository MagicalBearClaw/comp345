#include <algorithm>
#include <cmath>
#include <cassert>

#include "../includes/sentence_indexer.h"
#include "../includes/sentence_tokenizer_strategy.h"
#include "../includes/tokenizer.h"
#include "../includes/word_tokenizer_strategy.h"
#include "../includes/sentence.h"


// std::ifstream &operator >> (std::ifstream &ifs, Sentence_indexer &indexer)
// {
// 	return ifs;
// }
std::ostream & operator<<(std::ostream &ios, Sentence_indexer &indexer)
{
	for (std::vector<Indexer::itemTermIndex>::iterator element =  indexer.itis.begin(); element != indexer.itis.end(); ++element) {
		ios << std::get<0>(*element)->content();
	}
	ios << std::endl;
	return ios;
}
void operator >> (Index_item *doc, Sentence_indexer &indexer)
{
	std::vector<std::string> abreviations;
	std::ifstream abvsFile("resources/abbreviations.txt");
	assert(abvsFile.good() && "Invalid file name");
	while (!abvsFile.eof()) {
		std::string word;
		abvsFile >> word;
		abreviations.push_back(word);
	}

	int positionAcc = 0;
	SentenceTokenizerStrategy *strat = new SentenceTokenizerStrategy(abreviations);
	tokenizer tkz = tokenizer(strat);
	std::vector<std::string> sentences = tkz.tokenize(doc->content());
	for(std::vector<std::string>::iterator sentence = sentences.begin(); sentence != sentences.end(); ++sentence) {
		TermIndex tIdx;
		word_tokenizer_strategy *wStrat = new word_tokenizer_strategy();
		tokenizer tkzW = tokenizer(wStrat);
		std::vector<std::string> words = tkzW.tokenize(doc->content());
		for (std::vector<std::string>::iterator word = words.begin(); word != words.end(); ++word)
		{
			if (indexer.wftms.find(*word) != indexer.wftms.end())
			{
				std::get<1>(indexer.wftms[*word]) += 1;
			}
			else
			{
				indexer.wftms[*word] = std::make_tuple(*word, 1, 0);
			}
			tIdx.indexWord(*word);
		}
		Sentence *stnc = new Sentence(doc->name(), *sentence, positionAcc);
		positionAcc += sentence->length();
		indexer.itis.push_back(std::make_tuple(stnc, tIdx));
	}
	indexer.docNames.push_back(doc->name());
	indexer.normalized = false;
}

Sentence_indexer::Sentence_indexer()
{

}

Sentence_indexer::~Sentence_indexer()
{

}

std::vector<query_result> Sentence_indexer::query(std::string queryString, int numOfWords)
{
	if (!normalized) {
		normalize();
	}
	std::vector<query_result> results;
	TermIndex queryVector;
	std::vector<wordFrequencyTermMod> commons;
	word_tokenizer_strategy * strat = new word_tokenizer_strategy();
	tokenizer tkzr = tokenizer(strat);
	std::vector<std::string> queryWords = tkzr.tokenize(queryString);

	// generate query vector
	for(std::vector<std::string>::iterator word = queryWords.begin(); word != queryWords.end(); ++word) {
		std::unordered_map<std::string, wordFrequencyTermMod>::iterator element = wftms.find(*word);
		if (element != wftms.end() ) {
			queryVector.indexWord(*word);
			commons.push_back(element->second);
		}
	}
	queryVector.normalize(wftms);
	// compute scores and build result vector
	double commonModifier;
	double score;
	for(std::vector<itemTermIndex>::iterator item = itis.begin(); item != itis.end(); ++item) {
		double vectorProductAcc = 0.0;
		for (std::vector<wordFrequencyTermMod>::iterator common = commons.begin(); common != commons.end(); ++common) {
			commonModifier = std::get<2>(*common);
			vectorProductAcc += (std::get<1>(*item).termWeight(std::get<0>(*common), commonModifier) * queryVector.termWeight(std::get<0>(*common), commonModifier));
		}
		score = vectorProductAcc / (std::get<1>(*item).docNorm() * queryVector.docNorm());
		if (std::isnan(score)) {
			score = 0;
		}
		results.push_back(query_result(std::get<0>(*item), score));
	}
	// sort by document relevance if possible
	std::sort(results.begin(), results.end(), [](query_result a, query_result b) { return a.getItem()->name().length() > b.getItem()->name().length(); });
	std::sort(results.begin(), results.end(), [](query_result a, query_result b) { return a.getScore() > b.getScore(); });
	
	int totalLength = 0;
	std::vector<query_result> finalResults;
	
	// removes unecessary results
	for(std::vector<query_result>::iterator result = results.begin(); result != results.end() && totalLength < numOfWords; ++result) {
		finalResults.push_back(*result);
		totalLength += result->getItem()->size();
	}
	return finalResults;
}
