//Ng Wei Han, Ryan & Tay Rui-Jie
//S10163108C & S10178023E
//DSA Assignment - Spell Checker

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
int SpellCheck(Trie dictionary, string keyword, string* correctedWords, string* errors);
bool isAlpha(string target);
bool isInt(string target);

Trie dictionary;

int main()
{
	readDictionary(); //Initialization - Loading dictionary into data structure

	while (true) { 	//Menu

		Menu();

		if (isInt(temp)) {			//check if user input is an integer
			option = stoi(temp);	//convert user input to integer
			switch (option) {
			case 1:
				SpellCheckWord();			//Option 1 - Spell check a word
				break;
			case 2:
				SpellCheckFile();			//Option 2 - Spell check a file
				break;
			case 3:
				AddNewWord();				//Option 3 - Add a new word to the dictionary
				break;
			case 4:
				SaveDictionary();			//Option 4 - Save the dictionary (with new words added)
				break;
			case 5:
				DisplayAllWordsPrefix();	//Option 5 - Display all words that start with certain letters
				break;
				//case 6:					
				//	RemoveWord();			//Optional Feature - Remove word from dictionary
				//	break;
			case 0:							//End the program
				cout << "Bye!" << endl;
				return 0;
			default:						//if input was not one of the options
				cout << "Invalid input, please try again" << endl;
				break;
			}
		}
		else {		//if input was not an integer
			cout << "Invalid input, please try again" << endl;
		}
	}
}

//Display menu and prompt user for input
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

//Open dictionary file and load words into data structure
void readDictionary() {
	ifstream readDictionary;	//To open and read dictionary file
	string tempWord;			//To store words to be loaded into the dictionary data structure

	while (true) {		//Ask for dictionary file until valid dictionary is found
		cout << "Input dictionary file to be read: ";
		getline(cin, filename);

		filename = "../Resource Files/Dictionary Files/" + filename;
		readDictionary.open(filename, ios::in);	//Open dictionary file for reading

		if (!readDictionary) {	//If dictionary file does not exist
			cout << "Dictionary file does not exist." << endl << endl;
		}
		else {
			//Load words in dictionary into datastructure.
			while (readDictionary.good()) {
				readDictionary >> tempWord;
				dictionary.insert(tempWord);
			}
			break;
		}

		//Close dictionary after done
		readDictionary.close();
	}
}

//-------------------------------------------- Functions for options -----------------------------------------------------------

//Spell check a word - Option 1
//Search dictionary for word and prints to console if word exists in the dictionary.
//Also suggests possible mistyped words based on different errors (Insertion, transposition, deletion)
void SpellCheckWord() {
	string searchstring;			//To store word to be checked against the dictionary
	int n;							//For counting number of autocorrected words to suggest
	string correctedWords[10];		//For storing autocorrected words
	string errors[10];				//For storing error types

	cout << "Enter a keyword to search: ";
	getline(cin, searchstring);

	//Validate input (only accept input which contains alphabets)
	if (isAlpha(searchstring)) {
		//Check if input exists in dictionary
		if (dictionary.search(searchstring))
			cout << searchstring << " is present in the dictionary." << endl;
		else {	//Check for possible mistyped words
			n = SpellCheck(dictionary, searchstring, correctedWords, errors);

			//Display header
			cout << endl << "Word not found in the dictionary" << endl << "  " << string(46, '-') << endl;

			//Display autocorrected words (if any)
			if (correctedWords[0] != "-") {
				//Autocorrected word header
				cout << "  |  Similar word(s)" << string(dictionary.getHeight() - 15, ' ') << "  |  Type of Error  |" << endl << "  " << string(46, '-') << endl;

				//Display first autocorrected word and error (if any)
				cout << "  |  " << correctedWords[0] << string(dictionary.getHeight() - correctedWords[0].length(), ' ') << "  |  " << errors[0] << string(13 - errors[0].length(), ' ') << "  |" << endl;

				//Display additional autocorrected words and errors (if any)
				for (int i = 1; i < n; i++) {
					cout << "  |  " << correctedWords[i] << string(dictionary.getHeight() - correctedWords[i].length(), ' ') << "  |  " << errors[i] << string(13 - errors[i].length(), ' ') << "  |" << endl;
				}

				//Display line to close table
				cout << "  " << string(46, '-') << endl;
			}
			else { //If no similar words can be found in the dictionary
				cout << "No similar words found in the dictionary." << endl;
			}
		}
	}
	else {		//If input is invalid
		cout << "Invalid character(s). Please try again (Only alphabets without spaces are accepted)" << endl;
	}

}

//Spell check a file - Option 2
//Iterate through every word in a specified file and spell check against the dictionary.
//Prints words that do not exist in the dictionary, possible corrections and type of error to console.
void SpellCheckFile() {
	ifstream readTextFile;		//For opening and reading user specified file to check
	string input;				//For storing word to be checked against dictionary
	int count = 0;				//For counting and displaying error number when printing to console
	int n;						//For storing number of autocorrected words to suggest
	bool flag = false;			//For identifying if autocorrect header needs to be displayed

	cout << "Specify file to check against dictionary: ";
	getline(cin, filename);
	filename = "../Resource Files/Text Files/" + filename;
	readTextFile.open(filename, ios::in); //Open file for reading

	//Check if user specified file exists
	if (!readTextFile) {
		cout << "File not found. Please try again" << endl;
	}
	else {
		while (readTextFile.good()) {
			string correctedWords[10];		//For storing autocorrected words to suggest
			string errors[10];				//For storing error types

			readTextFile >> input;

			//If word does not exist in the dictionary
			if (!dictionary.search(input)) {
				//Determine if header autocorrected words need to be displayed
				if (!flag) {
					cout << endl << "Word(s) that are not found in the dictionary" << endl << "  " << string(79, '-') << endl;
					cout << "  | No." << "  |  " << "Mistakes" << string(dictionary.getHeight() - 8, ' ') << "  |  " << "Similar word(s)" + string(dictionary.getHeight() - 15, ' ') + "  |  Type of Error  |" << endl;
					cout << "  " << string(79, '-') << endl;
					flag = true;
				}

				//Return list of error types and possible autocorrected words
				n = SpellCheck(dictionary, input, correctedWords, errors);

				//Display first autocorrected word and error (if any)
				cout << "  |" << string(4 - to_string(count + 1).length(), ' ') << count + 1 << "  |  " << input << string(dictionary.getHeight() - input.length(), ' ') << "  |  ";
				cout << correctedWords[0] << string(dictionary.getHeight() - correctedWords[0].length(), ' ') << "  |  " << errors[0] << string(13 - errors[0].length(), ' ') << "  |" << endl;

				//Display additional autocorrected words and errors (if any)
				for (int i = 1; i < n; i++) {
					cout << "  |" << string(4, ' ') << "  |  " << string(dictionary.getHeight(), ' ') << "  |  ";
					cout << correctedWords[i] << string(dictionary.getHeight() - correctedWords[i].length(), ' ') << "  |  " << errors[i] << string(13 - errors[i].length(), ' ') << "  |" << endl;
				}
				count++;
			}
		}

		//Printing line to close table
		if (flag) {
			cout << "  " << string(79, '-') << endl;
		}

		//Print if no errors are found in the user specified file
		if (count == 0)
			cout << "All words in this text file are found in the dictionary." << endl;
	}
	readTextFile.close();
}

//Add a new word to the dictionary - Option 3
//Prompts user for input, adds new word to dictionary
void AddNewWord() {
	//Prompt user for new word to input
	cout << "Enter the new word: ";
	getline(cin, temp);

	//Check if user input is valid (only contains alphabets)
	if (isAlpha(temp)) {
		//Check if user input already exists in the dictionary
		if (dictionary.search(temp)) {
			cout << "\"" << temp << "\" already exists in the dictionary" << endl;
		}
		else { //if user input does not exist in the dictionary
			//Insert new word to trie dictionary
			dictionary.insert(temp);
			cout << "\"" << temp << "\" has been successfully added" << endl;
		}
	}
	else {	//if user input contains invalid characters
		cout << "Invalid character(s). Please try again" << endl;
	}

}

//Save the dictionary (with new words added) - Option 4
//Exports all words in the dictionary to a user specified file
void SaveDictionary() {
	//Prompt user for file to export to
	cout << "Specify file to save dictionary to: ";
	getline(cin, filename);
	filename = "../Resource Files/Text Files/" + filename;

	destinationfile.open(filename, ios::out);		//Open file to write dictionary to
	dictionary.printAllWords(&destinationfile);		//Print all words in dictionary to file
	destinationfile.close();						//Close file after done
}

//Display all words that start with certain letters - Option 5
//Prompts user for prefix (characters to start with) and prints all words that start with prefix to console
void DisplayAllWordsPrefix() {
	//Prompt user for characters to start with
	cout << "Enter prefix: ";
	getline(cin, temp);

	//Check if user input is valid (only alphabets)
	if (isAlpha(temp)) {
		dictionary.printAllWords(dictionary.getNode(temp), temp);	//Print all words starting with prefix to console
	}
	else {	//if user input contains invalid prefix
		cout << "\"" << temp << "\" is not a valid prefix. Please try again (Only alphabets accepted)." << endl;
	}
}

//Remove word from dictionary - Optional feature
//Remove a user specified word from the dictionary
void RemoveWord() {
	string temp;	//For storing user input

	//Prompt user for word to be removed
	cout << "Enter word to be removed: ";
	getline(cin, temp);

	//Check if user input exists in dictionary
	if (dictionary.search(temp)) {
		dictionary.remove(temp);		//Remove word from dictionary
		cout << "\"" << temp << "\" successfully removed from the dictionary" << endl;
	}
	else {	//If user input does not exist in dictionary
		cout << "\"" << temp << "\" does not exist in the dictionary" << endl;
	}
}

//------------------------------------------------- Additional Functions ----------------------------------------------------------

//Spellcheck function that suggests words based on error types detected in user input (Insertion, transposition, deletion)
//Returns number of autocorrected words, list of autocorrected words and list of respective error types
//Parses dictionary trie to search, keyword to search, list to store autocorrected words, list to store error types
int SpellCheck(Trie dictionary, string keyword, string* correctedWords, string* errors) {
	string autocorrect = keyword;
	int count = 0;

	//---------------------------------- Insertion error check -------------------------

	//Iterate through every alphabet in the keyword
	for (int i = 0; i < autocorrect.length(); i++) {
		//Remove each alphabet from the string
		autocorrect.erase(i, 1);

		//Check if modified string exist in dictionary
		if (dictionary.search(autocorrect)) {
			//Check if corrected word has already been accounted for
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
		autocorrect = keyword; //reset autocorrect for next error check
	}

	//---------------------------------- Transposition error check -------------------------

	//Iterate through every alphabet in the keyword (except last)
	for (int i = 0; i < autocorrect.length() - 1; i++) {

		//Swap adjacent letters 
		string prefix = autocorrect.substr(0, i);
		string postfix = autocorrect.substr(i + 2);
		autocorrect = prefix + autocorrect[i + 1] + autocorrect[i] + postfix;

		//Check if modified string exist in dictionary
		if (dictionary.search(autocorrect)) {
			//Check if corrected word has already been accounted for
			bool flag = false;
			for (int i = count - 1; i >= 0; i--) {
				flag = (autocorrect == correctedWords[i]);
			}

			//Add corrected word to list only if unaccounted for
			if (!flag) {
				correctedWords[count] = autocorrect;
				errors[count] = "Transposition";
				count++;
			}
		}
		autocorrect = keyword; //reset autocorrect for next error check
	}

	//------------------------------------ Deletion error check ----------------------------
	
	//Iterate through every alphabet in the keyword
	for (int i = 0; i <= autocorrect.length(); i++) {

		//Inserting character to string
		string prefix = autocorrect.substr(0, i);										//Set prefix to characters before index to insert character
		string postfix = autocorrect.substr(i);											//Set postfix to characters after index to insert character
		
		//Iterate through all possible alphabets (Only insert alphabets that are children of prefix)
		for (int x = 0; x < numberOfChar; x++) {
			if (dictionary.getNode(prefix) != NULL) {									//Check if there is a branch to prefix in dictionary
				if (dictionary.getNode(prefix)->children[x] != NULL) {					//Check if prefix node's child array contains alphabet to be inserted
					char extraCharacter = 'a' + x;										//Assign alphabet to be inserted
					autocorrect = prefix + extraCharacter + postfix;					//Insert alphabet into string to be evaluated

					//Check if modified string exist in dictionary
					if (dictionary.search(autocorrect)) {
						//Check if corrected word has already been accounted for
						bool flag = false;
						for (int i = count - 1; i >= 0; i--) {
							flag = (autocorrect == correctedWords[i]);
						}

						//Add corrected word to list only if unaccounted for
						if (!flag) {
							correctedWords[count] = autocorrect;
							errors[count] = "Deletion";
							count++;
						}
					}
					autocorrect = keyword; //reset autocorrect for next error check
				}
			}
		}
	}

	//---------------------------------- Substitution error check -------------------------

	for (int i = 0; i < autocorrect.length(); i++) {
		string prefix = autocorrect.substr(0, i);									//Set prefix to characters before index to replace character
		string postfix = autocorrect.substr(i + 1);									//Set postfix to characters after index to replace character
		
		for (int x = 0; x < numberOfChar; x++) {
			if (dictionary.getNode(prefix) != NULL) {									//Check if there is a branch to prefix in dictionary
				if (dictionary.getNode(prefix)->children[x] != NULL) {					//Check if prefix node's child array contains alphabet to be replaced
					char replacementChar = 'a' + x;										//Assign alphabet to be replaced
					autocorrect = prefix + replacementChar + postfix;					//Reconstruct word with replacement character

																						//Check if modified string exist in dictionary
					if (dictionary.search(autocorrect)) {
						//Check if corrected word has already been accounted for
						bool flag = false;
						for (int i = count - 1; i >= 0; i--) {
							flag = (autocorrect == correctedWords[i]);
						}

						//Add corrected word to list only if unaccounted for
						if (!flag) {
							correctedWords[count] = autocorrect;
							errors[count] = "Substitution";
							count++;
						}
					}
					autocorrect = keyword; //reset autocorrect for next error check
				}
			}
		}
	}

	//If there are no replacements found
	if (count == 0) {
		correctedWords[count] = "-";
		errors[count] = "-";
	}
	return count;
}

//Function that checks if specified string contains only alphabets (symbols and spaces not allowed)
//Returns a true of contains only alphabets and false if other characters detected
//Parses string to be checked
bool isAlpha(string target) {
	//Check if string is empty
	if (target == "")
		return false;

	//Iterate through every character in string
	for (int i = 0; i < target.length(); i++) {
		//If non-alphabetical character is detected
		if (!isalpha(target[i])) {
			return false;
		}
	}
	return true;
}

//Function that checks if specified string contains only integers (symbols and spaces not allowed)
//Returns a true of contains only integers and false if other characters detected
//Parses string to be checked
bool isInt(string target) {
	//Check if string is empty
	if (target == "")
		return false;

	//Iterate through every character in string
	for (int i = 0; i < target.length(); i++) {
		//If non-integer character is detected
		if (!isdigit(target[i])) {
			return false;
		}
	}
	return true;
}

/////////////////////////////////////BACKUP///////////////////////////////////
//string SpellCheck(Trie dictionary, string keyword) {
//	string autocorrect;
//	bool foundsimilar = false;
//
//	autocorrect = keyword;
//
//	for (int i = 0; i < autocorrect.length(); i++) { //Insertion error (extra char added)
//		autocorrect.erase(i, 1);
//		if (dictionary.search(autocorrect)) {
//			foundsimilar = true;
//			return autocorrect + string(dictionary.getHeight() - autocorrect.length(), ' ') + "  |  Insertion      |";
//		}
//
//		else
//			autocorrect = keyword; //reset autocorrect to delete second char
//	}
//
//	for (int i = 0; i < autocorrect.length() - 1; i++) { //Transposition error (two adjancent char swapped)
//
//		string prefix = autocorrect.substr(0, i);
//		string postfix = autocorrect.substr(i + 2);
//		autocorrect = prefix + autocorrect[i + 1] + autocorrect[i] + postfix;
//
//		if (dictionary.search(autocorrect)) {
//			foundsimilar = true;
//			return autocorrect + string(dictionary.getHeight() - autocorrect.length(), ' ') + "  |  Transposition  |";
//		}
//
//		else
//			autocorrect = keyword; //reset autocorrect to delete second word
//	}
//
//	if (!foundsimilar)
//		return "-" + string(dictionary.getHeight() - 1, ' ') + "  |  -              |";
//}