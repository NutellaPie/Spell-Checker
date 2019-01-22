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
string filename; // Filenames of various files used in this program
ofstream destinationfile; // Open destination file for Option 4

//--------------------Initialization--------------------
void Menu();
void readDictionary();
void option1();
void option2();
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
				option1();
				break;
			case 2:
				option2();
				break;
			case 3:
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

				if (isAlpha(temp)) {
					dictionary.printAllWords(dictionary.getNode(temp), temp);
				}
				else {
					cout << "\"" << temp << "\" is not a valid prefix. Please try again (Only alphabets accepted)." << endl;
				}
				break;
				//case 6:
				//	option6();
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
	cout << "[5] Display all words in the dictionary that starts with a certain letters" << endl;
	//cout << "[6] Remove a word from the dictionary" << endl;
	cout << "[0] Exit " << endl;
	cout << "----------------------------------------------" << endl;
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

void option1() {
	string searchstring;
	string autocorrect;
	string wrongwords[50];
	int count = 0;

	cout << "Enter a keyword to search: ";
	cin >> searchstring;

	if (dictionary.search(searchstring))
		cout << searchstring << " is present in the dictionary." << endl;

	else {
		cout << searchstring << " is not present in the dictionary." << endl;

		autocorrect = searchstring;

		for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
			autocorrect.erase(i, 1);
			if (dictionary.search(autocorrect)) {
				cout << "Insertion error. Did you mean: " << autocorrect << endl;
			}

			else
				autocorrect = searchstring; //reset autocorrect
		}

		for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
			swap(autocorrect[i], autocorrect[i + 1]);
			if (dictionary.search(autocorrect)) {
				cout << "Transposition error. Did you mean: " << autocorrect << endl;
			}

			else
				autocorrect = searchstring; //reset autocorrect
		}
	}
}

void option2() {
	ifstream readTextFile;
	string temp;
	bool flag = false;
	string autocorrect;
	string wrongwords[50];
	int count = 0;

	cout << "Specify file to check against dictionary: ";
	cin >> filename;
	filename = "../Resource Files/Text Files/" + filename;
	readTextFile.open(filename, ios::in); //Open file for reading

	while (readTextFile.good()) {

		readTextFile >> temp;

		if (!dictionary.search(temp)) {

			if (flag) {
				cout << "List of words not in dictionary:" << endl;
				flag = true;
			}

			autocorrect = temp;

			for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
				autocorrect.erase(i, 1);
				if (dictionary.search(autocorrect)) {
					wrongwords[count] = "\"" + temp + "\" (Insertion error) " + "[Did you mean: " + autocorrect + "]";
					count++;
				}

				else
					autocorrect = temp; //reset autocorrect
			}

			for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
				swap(autocorrect[i], autocorrect[i + 1]);
				if (dictionary.search(autocorrect)) {
					wrongwords[count] = "\"" + temp + "\" (Transposition error) " + "[Did you mean: " + autocorrect + "]";
					count++;
				}

				else
					autocorrect = temp; //reset autocorrect
			}
		}
	}

	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". " << wrongwords[i] << endl;
	}

	if (count == 0)
		cout << "All words in this text file are found in the dictionary." << endl;

	readTextFile.close();
}

bool isAlpha(string target) {
	for (int i = 0; i < target.length(); i++) {
		if (!isalpha(target[i])) {
			return false;
		}
	}
	return true;
}

//void option6() {
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
