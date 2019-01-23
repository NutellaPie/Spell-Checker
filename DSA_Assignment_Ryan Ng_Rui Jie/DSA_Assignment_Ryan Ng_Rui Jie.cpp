#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

//--------------------Variables--------------------
int option; // Option selected by user
string temp; // Store the user input
string filename; // Filenames of various files used in this program
ofstream destinationfile; // Open destination file for Option 4

//--------------------Function Initialization--------------------
void Menu();
void readDictionary();
void SpellCheckWord();
void SpellCheckFile();
void AddNewWord();
void SaveDictionary();
void DisplayAllWordsPrefix();
//void RemoveWord();
//string SpellCheck(Trie dictionary, string keyword);
int SpellCheck(Trie dictionary, string keyword, string* correctedWords, string* errors);
bool isAlpha(string target);
bool isInt(string target);

Trie dictionary;

int main()
{
	readDictionary(); //Initialization

	while (true) { 	//Menu

		Menu();

		if (isInt(temp)) {			//check if user input is an integer
			option = stoi(temp);	//convert user input to integer
			switch (option) {
			case 1:
				//SpellCheckWord();
				break;
			case 2:
				SpellCheckFile();
				break;
			case 3:
				AddNewWord();
				break;
			case 4:
				SaveDictionary();
				break;
			case 5:
				DisplayAllWordsPrefix();
				break;
				//case 6:					//Optional - Remove word from dictionary
				//	RemoveWord();
				//	break;
			case 0:
				cout << "Bye!" << endl;
				return 0;
			default:	//if input was not one of the options
				cout << "Invalid input, please try again" << endl;
				break;
			}
		}
		else {		//if input was not an integer
			cout << "Invalid input, please try again" << endl;
		}
	}
}


void Menu() {
	cout << endl << "---------------- Spell Checker -------------------" << endl;
	cout << "[1] Spell check a word" << endl;
	cout << "[2] Spell check a file" << endl;
	cout << "[3] Add a new word to the dictionary" << endl;
	cout << "[4] Save the dictionary (with new words added)" << endl;
	cout << "[5] Display all words in the dictionary that starts with certain letters" << endl;
	//cout << "[6] Remove a word from the dictionary" << endl;			//optional option
	cout << "[0] Exit " << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Enter your option : ";

	getline(cin, temp);

	cout << endl;
}

void readDictionary() {
	ifstream readDictionary;
	string tempWord;

	while (true) {
		cout << "Input dictionary file to be read: ";
		getline(cin, filename);

		filename = "../Resource Files/Dictionary Files/" + filename;
		readDictionary.open(filename, ios::in);

		if (!readDictionary) {
			cout << "Dictionary file does not exist." << endl << endl;
		}
		else {
			while (readDictionary.good()) {
				readDictionary >> tempWord;
				dictionary.insert(tempWord);
			}
			break;
		}

		readDictionary.close();
	}
}

//-------------------------Fuctions for options----------------------------
//Spell check a file - Option 1
//void SpellCheckWord() {
//	string searchstring;
//
//	cout << "Enter a keyword to search: ";
//	getline(cin, searchstring);
//
//	if (isAlpha(searchstring)) {
//		if (dictionary.search(searchstring))
//			cout << searchstring << " is present in the dictionary." << endl;
//
//		else {
//			cout << endl << "Word not found in the dictionary" << endl << string(70, '-') << endl;
//			cout << "Mistakes" << string(dictionary.getHeight() - 8, ' ') << "  |  " << "Similar word(s)" + string(dictionary.getHeight() - 15, ' ') + "  |  Type of Error  |" << endl;
//			cout << string(70, '-') << endl;
//			cout << searchstring << string(dictionary.getHeight() - searchstring.length(), ' ') << "  |  " << SpellCheck(dictionary, searchstring) << endl;
//			cout << string(70, '-') << endl;
//		}
//	}
//	else {
//		cout << "Invalid character(s). Please try again (Only alphabets without spaces are accepted)" << endl;
//	}
//
//}

//Spell check a file - Option 2
void SpellCheckFile() {
	ifstream readTextFile;
	string input;
	int count = 0;
	int n;
	bool flag = false;

	cout << "Specify file to check against dictionary: ";
	getline(cin, filename);
	filename = "../Resource Files/Text Files/" + filename;
	readTextFile.open(filename, ios::in); //Open file for reading

	if (!readTextFile) {
		cout << "File not found. Please try again" << endl;
	}
	else {
		while (readTextFile.good()) {
			//Arrays for storing autocorrected words and error types
			string correctedWords[10];
			string errors[10];

			readTextFile >> input;

			if (!dictionary.search(input)) {
				if (!flag) {
					cout << endl << "Word(s) that are not found in the dictionary" << endl << string(79, '-') << endl;
					cout << " No." << "  |  " << "Mistakes" << string(dictionary.getHeight() - 8, ' ') << "  |  " << "Similar word(s)" + string(dictionary.getHeight() - 15, ' ') + "  |  Type of Error  |" << endl;
					cout << string(79, '-') << endl;
					flag = true;
				}

				n = SpellCheck(dictionary, input, correctedWords, errors);

				//Display first error (if any)
				cout << string(4 - to_string(count + 1).length(), ' ') << count + 1 << "  |  " << input << string(dictionary.getHeight() - input.length(), ' ') << "  |  ";
				cout << correctedWords[0] << string(dictionary.getHeight() - correctedWords[0].length(), ' ') << "  |  " << errors[0] << string(13 - errors[0].length(), ' ') << "  |" << endl;

				//Display additional errors (if any)
				for (int i = 1; i < n; i++) {
					cout << string(4, ' ') << "  |  " << string(dictionary.getHeight(), ' ') << "  |  ";
					cout << correctedWords[i] << string(dictionary.getHeight() - correctedWords[i].length(), ' ') << "  |  " << errors[i] << string(13 - errors[i].length(), ' ') << "  |" << endl;
				}
				count++;
			}
		}
		if (flag) {
			cout << string(79, '-') << endl;
		}

		if (count == 0)
			cout << "All words in this text file are found in the dictionary." << endl;
	}
	readTextFile.close();
}

//Add a new word to the dictionary - Option 3
void AddNewWord() {
	//Prompt user for new word to input
	cout << "Enter the new word: ";
	getline(cin, temp);

	if (isAlpha(temp)) {
		if (dictionary.search(temp)) {
			cout << "\"" << temp << "\" already exists in the dictionary" << endl;
		}
		else {
			//Insert new word to trie dictionary
			dictionary.insert(temp);
			cout << "\"" << temp << "\" has been successfully added" << endl;
		}
	}
	else {
		cout << "Invalid character(s). Please try again" << endl;
	}

}

//Save the dictionary (with new words added) - Option 4
void SaveDictionary() {
	cout << "Specify file to save dictionary to: ";
	getline(cin, filename);
	filename = "../Resource Files/Text Files/" + filename;

	destinationfile.open(filename, ios::out);
	dictionary.printAllWords(&destinationfile);
	destinationfile.close();
}

//Display all words that start with certain letters - Option 5
void DisplayAllWordsPrefix() {
	cout << "Enter prefix: ";
	getline(cin, temp);

	if (isAlpha(temp)) {
		dictionary.printAllWords(dictionary.getNode(temp), temp);
	}
	else {
		cout << "\"" << temp << "\" is not a valid prefix. Please try again (Only alphabets accepted)." << endl;
	}
}

//Remove word from dictionary - Optional option
//void RemoveWord() {
//	string temp;
//
//	cout << "Enter a keyword to remove: ";
//	getline(cin, temp);
//
//	if (dictionary.search(temp)) {
//		dictionary.remove(temp);
//		cout << "Successfull" << endl;
//	}
//	else {
//		cout << "Does not exist" << endl;
//	}
//}

//-------------------------------Additional Functions-----------------------
int SpellCheck(Trie dictionary, string keyword, string* correctedWords, string* errors) {
	string autocorrect = keyword;
	int count = 0;

	//---------------------------------- Insertion error check -------------------------

	for (int i = 0; i < autocorrect.length(); i++) { 
		autocorrect.erase(i, 1);
		if (dictionary.search(autocorrect)) {		//check if modified string exist in dictionary
			//check if corrected word is already accounted for
			bool flag = false;
			for (int i = count - 1; i >= 0; i--) {
				flag = (autocorrect == correctedWords[i]);
			}

			//Add corrected word to list only if unaccounted for
			if (!flag) {
				correctedWords[count] = autocorrect;
				errors[count] = "Insertion";
				count++;
			}
		}
		autocorrect = keyword; //reset autocorrect 
	}

	//---------------------------------- Transposition error check -------------------------

	for (int i = 0; i < autocorrect.length() - 1; i++) { 

		//Swap adjacent letters 
		string prefix = autocorrect.substr(0, i);
		string postfix = autocorrect.substr(i + 2);
		autocorrect = prefix + autocorrect[i + 1] + autocorrect[i] + postfix;

		if (dictionary.search(autocorrect)) {		//check if modified string exist in dictionary
			bool flag = false;
			for (int i = count - 1; i >= 0; i--) {
				flag = (autocorrect == correctedWords[i]);
			}
			if (!flag) {
				correctedWords[count] = autocorrect;
				errors[count] = "Transposition";
				count++;
			}
		}
		autocorrect = keyword; //reset autocorrect
	}

	if (count == 0) { //If there are no replacements found
		correctedWords[count] = "-";
		errors[count] = "-";
	}
	return count;
}

bool isAlpha(string target) {
	if (target == "")
		return false;
	for (int i = 0; i < target.length(); i++) {
		if (!isalpha(target[i])) {
			return false;
		}
	}
	return true;
}

bool isInt(string target) {
	if (target == "")
		return false;
	for (int i = 0; i < target.length(); i++) {
		if (!isdigit(target[i])) {
			return false;
		}
	}
	return true;
}