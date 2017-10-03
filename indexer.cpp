// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
#include "indexer.h"
// temporary to use string as stream

std::vector<std::string> stopWords = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during", "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers", "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours	", "ourselves", "out", "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them", "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours", "yourself", "yourselves"};

int main()
{
  Indexer *indexer = new Indexer();
  std::ifstream ifs("index.txt");
  assert(ifs.good() && "Invalid file name");
  while (!ifs.eof())
  {
    ifs >> *indexer;
  }
  std::cout << *indexer;
  std::cout << "done" << std::endl;
  // fs >> indexer;
}

Indexer::Indexer()
{
  // documents = {};
}

std::ifstream &operator>>(std::ifstream &ifs, Indexer &indexer)
{
  std::string fileNm;
  if (ifs >> fileNm)
  {
    std::cout << fileNm << std::endl;
    indexer.createDocument(fileNm);
    indexer.docNames.push_back(fileNm);
    std::ifstream docIfs(fileNm);
    assert(docIfs.good() && "Invalid file name"); // good even if vscode complains :/
    char *punctuations = "_{}[]#()<>%:;.?*+^&|~!=,\"'\0";
    Document* doc = indexer[fileNm];
    while (!docIfs.eof())
    {
      std::string word;
      if (docIfs >> word)
      {
        char *cursor = punctuations;
        do
        {
          int pos = word.find(*cursor);
          if (pos != -1)
          {
            word.replace(pos, 1, "");
          }
        } while (*(++cursor));
        if (std::find(stopWords.begin(), stopWords.end(), word) == stopWords.end())
        {
          std::cout << word << std::endl;
          indexer.words.push_back(word);
          doc->indexWord(word);
        }
      }
      // do file reading stuff for documents
    }
  }
}

void indexWord(WordCtr &dict, std::string &word)
{
  if (dict.find(word) == dict.end())
  { // checks if word does not exist
    dict[word] = 1;
  }
  else
  {
    dict[word]++;
  }
}

void Indexer::createDocument(std::string &name)
{
  documents[name] = new Document();
}

void Indexer::addWord(std::string &docName, std::string &word)
{
  // add document if none exists
  if (documents.find(docName) == documents.end())
  {
    createDocument(docName);
  }
  documents[docName]->indexWord(word); // move this logic into this method
}

Document *Indexer::operator[](std::string docName)
{
  if (documents.find(docName) == documents.end())
  {
    return nullptr;
  }
  return documents[docName];
}


std::ostream & operator<<(std::ostream &ios, Indexer &indexer) {
  for (std::vector<std::string>::const_iterator i = indexer.words.begin(); i != indexer.words.end(); i++) {
    ios << *i << " ";
    for (std::vector<std::string>::iterator j = indexer.docNames.begin(); j != indexer.docNames.end(); j++) {
      ios << (*indexer[*j])[*i] << " ";
    }
    ios << std::endl;
  }
}