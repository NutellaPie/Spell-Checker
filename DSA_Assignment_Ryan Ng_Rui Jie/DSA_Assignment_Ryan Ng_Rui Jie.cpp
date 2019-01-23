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

//--------------------Initialization--------------------
void Menu();
void readDictionary();
void SpellCheckWord();
void SpellCheckFile();
void AddNewWord();
void SaveDictionary();
void DisplayAllWordsPrefix();
//void RemoveWord();
string SpellCheck(Trie dictionary, string keyword);
bool isAlpha(string target);
//void option6(); // Optional delete function

Trie dictionary;

int main()
{
	readDictionary(); //Initialization

	while (true) { 	//Menu

		Menu();

		if (cin.good() && option >= 0 && option <= 5) {		//Validate input to only accept integers 0 to 5
			switch (option) {
			case 1:
				SpellCheckWord();
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
			}
		}
		else {		//if input was not valid
			cin.clear();											//Clear cin failbit
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Flush buffer
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

	cin >> option;
	cout << endl;
}

void readDictionary() {
	ifstream readDictionary;
	string tempWord;

	while (true) {
		cout << "Input dictionary file to be read: ";
		cin >> filename;

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
void SpellCheckWord() {
	string searchstring;

	cout << "Enter a keyword to search: ";
	cin >> searchstring;

	if (dictionary.search(searchstring))
		cout << searchstring << " is present in the dictionary." << endl;

	else
		cout << "\"" << searchstring << "\" is not present in the dictionary. " << SpellCheck(dictionary, searchstring) << endl;

}

//Spell check a file - Option 2
void SpellCheckFile() {
	ifstream readTextFile;
	string input;
	int count = 0;
	bool flag = false;

	cout << "Specify file to check against dictionary: ";
	cin >> filename;
	filename = "../Resource Files/Text Files/" + filename;
	readTextFile.open(filename, ios::in); //Open file for reading

	while (readTextFile.good()) {

		readTextFile >> input;

		if (!dictionary.search(input)) {
			if (!flag) {
				cout << endl << "Word(s) that are not found in the dictionary" << endl;
				flag = true;
			}

			cout << count + 1 << ". \"" << input << "\" is not present in the dictionary. " << SpellCheck(dictionary, input) << endl;
			count++;
		}
	}

	if (count == 0)
		cout << "All words in this text file are found in the dictionary." << endl;

	readTextFile.close();
}		

//Add a new word to the dictionary - Option 3
void AddNewWord() {
	//Prompt user for new word to input
	cout << "Enter the new word: ";
	cin >> temp;

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
	cin >> filename;
	filename = "../Resource Files/Text Files/" + filename;

	destinationfile.open(filename, ios::out);
	dictionary.printAllWords(&destinationfile);
	destinationfile.close();
}

//Display all words that start with certain letters - Option 5
void DisplayAllWordsPrefix() {
	cout << "Enter prefix: ";
	cin >> temp;

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
//	cin >> temp;
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
string SpellCheck(Trie dictionary, string keyword) {
	string autocorrect;
	bool foundsimilar = false;

	autocorrect = keyword;

	for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
		autocorrect.erase(i, 1);
		if (dictionary.search(autocorrect)) {
			return "Did you mean \"" + autocorrect + "\" ? (Insertion error)";
			foundsimilar = true;
		}

		else
			autocorrect = keyword; //reset autocorrect to delete second char
	}

	for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
		swap(autocorrect[i], autocorrect[i + 1]);
		if (dictionary.search(autocorrect)) {
			return "Did you mean \"" + autocorrect + "\" ? (Transposition error)";
			foundsimilar = true;
		}

		else
			autocorrect = keyword; //reset autocorrect to delete second word
	}

	if (!foundsimilar)
		return "There are also no similar words found in the dictionary.";
}

bool isAlpha(string target) {
	for (int i = 0; i < target.length(); i++) {
		if (!isalpha(target[i])) {
			return false;
		}
	}
	return true;
}