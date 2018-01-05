
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;

void read_dictionary(ifstream &in_file, set<string> &dictionary, int &bad){

	string word;
	bool bad_word = false;
	if (in_file.fail())
	{
		cout << "\nCouldn't load file\n\n" << endl;
		bad = 0;
	}
	else{

		while (in_file >> word)
		{
			for (size_t spot = 0; spot < word.size(); spot++){
				if (!isalpha(word[spot])){
					spot = word.size();
					bad_word = true;
				}
				else{
					if (isupper(word[spot])){
						word[spot] = tolower(word[spot]);
					}
				}
			}
			if (bad_word == false){

				dictionary.insert(word);
			}
			bad_word = false;
		}
		in_file.close();
	}
}

void search_input(string &word, set<string> dictionary, map<string, vector<int>> &document, int counter){
	
	bool bad_word = true;
	for (size_t spot = 0; spot < word.size(); spot++){
		
		if (isupper(word[spot])){
			word[spot] = tolower(word[spot]);
		}
	}	
	for (auto dic : dictionary){
		if (dic == word){
			bad_word = false;
		}
			
	}
	if (bad_word == true){
		if (word == ""){
		}
		else{
			document[word].push_back(counter);
		}					
								
	}
}

void spell_checker(string line, map<string, vector<int>> &document, set<string> dictionary, int counter){
	stringstream ss;
	string word;
		
	for (size_t i = 0; i<line.size(); i++){
		if (!isalpha(line[i])){
			line.replace(i,1," ");
		}
	}
	ss << line;
	while (ss >> word){
		
		search_input(word, dictionary, document, counter);
	}		
}

void read_document(ifstream &in_file, map<string, vector<int>> &document, int &bad, set<string> dictionary){
	
	string line;
	
	if (in_file.fail())
	{
		cout << "\nCouldn't load file\n\n" << endl;
		bad = 0;
	}
	else{
		int counter = 1;
		while (getline(in_file, line))
		{
			spell_checker(line, document, dictionary, counter);
			counter++;
		}
		in_file.close();
	}
}

//---------------------------------------------------------------------------------------
int main(int argc, char* argv[]){

	set<string> dictionary;
	map<string, vector<int>> document;
	ifstream in_file;
	ofstream out_file;
	int bad = 1;

	in_file.open(argv[1]);

	read_dictionary(in_file, dictionary, bad);

	if (bad == 0){

		return 0;
	}
	
	in_file.open(argv[2]);

	read_document(in_file, document, bad, dictionary);

	if (bad == 0){

		return 0;
	}
	out_file.open(argv[3]);
	for (auto spot : document)
	{
		out_file << spot.first << ": ";
		for (auto slot : spot.second)
		{
			out_file << slot << " ";
		}
		out_file << endl;
	}

	return 0;
}
//---------------------------------------------------------------------------------------
