#include "../includes/document_indexer.h"
#include "../includes/util.h"

//Works like defined in assignment #2 indexing and querying complete documents
// doc specific
std::ifstream &operator>>(std::ifstream &ifs, DocumentIndexer &indexer)
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
        Document doc(docName);
        doc >> indexer; // "stream" document into indexer
    }

    return ifs;
}
