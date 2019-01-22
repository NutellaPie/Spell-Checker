#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

#pragma comment(linker, "/STACK:256000000")
#pragma comment(linker, "/HEAP:256000000")

using namespace std;

//--------------------Variables--------------------
int option; // Option selected by user
string temp; // Store the user input
bool specialchars = false; // To check for special characters in user input
string filename; // Filenames of various files used in this program
ofstream destinationfile; // Open destination file for Option 4

//--------------------Initialization--------------------
void Menu();
void readDictionary();
void SpellCheckWord();
void SpellCheckFile();
string SpellCheck(Trie dictionary, string keyword);
//void option6(); // Optional delete function

Trie dictionary;

int main()
{
	readDictionary(); //Initialization

	while (true) { 	//Menu

		Menu();

		switch (option) {
		case 1:
			SpellCheckWord();
			break;
		case 2:
			SpellCheckFile();
			break;
		case 3:
			//Prompt user for new word to input
			cout << "Enter the new word: ";
			cin >> temp;

			for (int i = 0; i < temp.length(); i++) {
				if (!isalpha(temp[i])) {
					specialchars = true;
					break;
				}
			}

			if (!specialchars) {
				//Insert new word to trie dictionary
				dictionary.insert(temp);
				cout << "\"" << temp << "\"" << " has been successfully added" << endl;
			}

			else {
				cout << "Invalid character(s). Please try again" << endl;
				specialchars = false;
			}

			break;
		case 4:
			cout << "Specify file to save dictionary to: ";
			cin >> filename;
			filename = "../Resource Files/Text Files/" + filename;

			destinationfile.open(filename, ios::out);
			dictionary.printAllWords(&destinationfile);
			destinationfile.close();
			break;
		case 5:
			cout << "Enter prefix: ";
			cin >> temp;
			dictionary.printAllWords(dictionary.getNode(temp), temp);
			break;
			//case 6:
			//	option6();
			//	break;
		case 100:

			break;
		case 0:
			cout << "Bye!" << endl;
			return 0;
		}
	}
}

void Menu() {
	cout << endl << "---------------- Spell Checker -------------------" << endl;
	cout << "[1] Spell Check a Word" << endl;
	cout << "[2] Spell Check a File" << endl;
	cout << "[3] Add a New Word to the Dictionary" << endl;
	cout << "[4] Save the Dictionary (With New Words Added)" << endl;
	cout << "[5] Display All Words in the Dictionary that Starts with a Certain Letter" << endl;
	//cout << "[6] Remove a word from the dictionary" << endl;
	cout << "[100] Option for testing" << endl;
	cout << "[0] Exit " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Enter your option : ";

	cin >> option;

	cout << endl;
}

void readDictionary() {
	ifstream readDictionary;
	string tempWord;

	cout << "Input dictionary file to be read: ";
	cin >> filename;

	filename = "../Resource Files/Dictionary Files/" + filename;
	readDictionary.open(filename, ios::in);

	while (readDictionary.good()) {
		readDictionary >> tempWord;
		dictionary.insert(tempWord);
	}

	readDictionary.close();
}

void SpellCheckWord() {
	string searchstring;

	cout << "Enter a keyword to search: ";
	cin >> searchstring;

	if (dictionary.search(searchstring))
		cout << searchstring << " is present in the dictionary." << endl;

	else
		cout << "\"" << searchstring << "\" is not present in the dictionary. " << SpellCheck(dictionary, searchstring) << endl;

}

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