#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <fstream>		// std:ifstream file
#include <vector>		// unused
#include <algorithm>	// std::replace
#include <map>			// std::map

using namespace std; //am i using this wrong?
//#include indexer.h //build the interface

class DocumentIndexer {
public:
	int run()
	{
		//Make a call to the retrieval method
		listOfFiles = retrieve_files("index.txt");

		//for each file in the listOfFiles
		//TODO

		//Retrieve the contents of the first file
		std::ifstream file("file1.txt");

		build_dictionary(file);


		return 0;
	}//end of main

	
	private:
		//use a multimap instead?
		std::map<std::string, int> dictionary;
		//List of all the files to parse (found in inxes.txt)
		std::vector<std::string> listOfFiles;



	//This method will read a list of files from index.txt
	std::vector<std::string> retrieve_files(const std::string& path)
	{
		//read the list of files names from index.txt
		std::vector<string> listOfFileNames;
		return listOfFileNames;

		std::ifstream file(path);

		if (!file.is_open()) //Check if the file can be opened.
		{
			std::cerr << "Unable to open file" << "\n";
			std::exit(-1);
		}

		std::vector<string> fileNames;//this vector will be returned 
		std::string token;

		while (std::getline(file, token, '\n'))
		{
			fileNames.push_back(token);
		}

		return fileNames;
	}

	//This method will accept a file and fill the dictionary with all words  and count instances of that word.
	void build_dictionary(ifstream& file) {

		//Not a fast solution?
		//Not an efficient solution?
		if (file)
		{
			std::stringstream bufferedStream;

			bufferedStream << file.rdbuf();

			file.close();

			// operations on the buffer...

			//std::cout << bufferedStream.str();

			std::string streamContent = bufferedStream.str();

			std::cout << "Before: " << bufferedStream.str() << std::endl;

			//std::replace(streamContent.begin(), streamContent.end(), '.', '@');
			//learn to use replaceif

			cout << "-------------------" << endl;

			std::transform(std::begin(streamContent), std::end(streamContent), std::begin(streamContent), [](auto ch) {
				switch (ch) {
				case ',':
					return ' ';
				case '.':
					return ' ';
				case '/':
					return ' ';
				}
				return ch;
			});

			bufferedStream.str(streamContent);

			std::cout << "After: " << bufferedStream.str() << std::endl;

			//std::cout << bufferedStream.str();

			//read word by word into the dictionary


			//std::stringstream ss;
			//cout << "Hello, universe!" << endl;

		}
		return;
	}

};

int main() {
	DocumentIndexer d;
	return d.run();
}

