//Ng Wei Han, Ryan & Tay Rui-Jie
//S10163108C & S10178023E
//DSA Assignment - Spell Checker

#include "pch.h"
#include "Trie.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//-------------------------------------------------------- Helper Functions -------------------------------------------------------------------

//Function to print word to console based on array of chars
//Prints word to console
//Parses array of characters to be printed, number of characters to print, prefix (if any)
void printWord(char* str, int n, string prefix) {
	//Print prefix to console (if any)
	cout << prefix;
	
	//Iterate through array to print 'n' number of chars to console
	for (int i = 0; i < n; i++) {
		cout << str[i];
	}
	cout << endl;
}

//Function to print word to external file based on array of chars
//Prints word to external file
//Parses array of characters to be printed, number of characters to print, external file to be printed to
void printWord(char* str, int n, ofstream* destinationfile) {
	//Iterate through array to print 'n' number of chars to file
	for (int i = 0; i < n; i++) {
		*destinationfile << str[i];
	}
	*destinationfile << endl;
}

//-------------------------------------------------------- Trie Class Functions ----------------------------------------------------------------

//Trie Constructor
Trie::Trie() {
	root = new TrieNode();			//Create root trieNode
	height = 0;						//Set height of trie to 0
}

//Function used to set the height property of the trie
//Parses an integer height
void Trie::setHeight(int h) {
	height = h;
}

//Function used to get the height property of the trie
//Returns the height of the trie as an integer
int Trie::getHeight() {
	return height;
}

//Function used to search for a string in the trie
//Returns a boolean value of true if string exists in the trie and false if it does not
//Parses a string to be searched in the trie
bool Trie::search(string target) {
	TrieNode* temp = root;										//Temporary TrieNode pointer used to traverse the trie

	//Iterate through the characters of the string
	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);				//Converts character to lowercase

		//Traverse to next node if character is a child of current node
		if (temp->children[currentCharacter - 'a'] != NULL)
			temp = temp->children[currentCharacter - 'a'];
		else
			return false;										//Return false if character is not child of current node
	}
	return temp->endOfWord;		//Return boolean value which determines if last character of target completes a word
}

//Function used to insert a string into the trie
//Parses a string to be inserted into the trie
void Trie::insert(string target) {
	//Check if string to insert already exist in dicitonary
	TrieNode* temp = root;
	if (!search(target)) {											

		//Set height of trie to longest word
		if (target.length() > getHeight()) {
			setHeight(target.length());
		}

		//Iterate through each character in the string
		for (int i = 0; i < target.length(); i++) {
			char currentCharacter = tolower(target[i]);				//Convert char to lowercase

			//Create new trieNode if it does not exist in trie
			if (temp->children[currentCharacter - 'a'] == NULL) {	
				TrieNode* newNode = new TrieNode();
				temp->children[currentCharacter - 'a'] = newNode;
			}

			temp = temp->children[currentCharacter - 'a'];			//Traverse to the next trie node
		}

		temp->endOfWord = true;										//Set endOfWord bool to true to indicate that the character completes the word
	}
}


//Functions used to remove a string from the trie (Recursively delete nodes from bottom of trie)

//Returns function call to primary remove function with default values
//Parses string to be removed
TrieNode* Trie::remove(string target) {
	return remove(root, target);		//Calls primary remove function with default values
}

//Primary remove function
//Returns a TrieNode to be used to recursively delete nodes
//Parses trienode to start from, string to be removed, current depth of trie
TrieNode* Trie::remove(TrieNode* root, string target, int level) {
	//Check if trie is empty;
	if (isEmpty(Trie::root)) {
		return NULL;
	}

	//Base case (Last character of the target string to be removed)
	if (level == target.length()) {
		//Indicate that character is no longer the end of a word
		if (root->endOfWord) {
			root->endOfWord = false;
		}

		//Remove if character is not prefix for any other word
		if (isEmpty(root)) {
			delete root;
			root = NULL;
		}

		return root;
	}

	//Recursive step (traverse to last character of string to be deleted)
	root->children[target[level] - 'a'] = remove(root->children[target[level] - 'a'], target, level + 1);

	//Delete node if character is not the prefix for another word && is not the end of a word
	if (isEmpty(root) && root->endOfWord == false) {
		delete root;
		root = NULL;
	}

	return root;
}


//Function used to check if trie has any children
//Returns a boolean value of true if there is no children and false if it has children
//Parses TrieNode pointer to be checked
bool Trie::isEmpty(TrieNode* root) {
	//Iterate through children array of TrieNode
	for (int i = 0; i < numberOfChar; i++) {
		//Return false if a child node is detected
		if (root->children[i] != NULL) {
			return false;
		}
	}
	return true;
}

//Function used to return a pointer to a particular TrieNode
//Returns a pointer to a specified TrieNode within the trie (Return's NULL if target does not exist)
//Parses a string to traverse through
TrieNode* Trie::getNode(string target) {
	TrieNode* temp = root;											//Temporary pointer used to traverse the trie

	//Iterate through every character in the target string
	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);					//Convert character to lowercase

		if (temp->children[currentCharacter - 'a'] != NULL) {
			temp = temp->children[currentCharacter - 'a'];			//Traverse to next node if character is a child of the current node
		}
		else {
			return NULL;											//Return NULL if character is not a child of current node
		}
	}
	return temp;													//Return pointer to target node
}


//Functions used to print words in dictionary to console

//Returns function call to primary (console) printAllWords function with default values
void Trie::printAllWords() {
	//Dynamically initialise array with size of max length of string in dictionary
	char* wordArray = NULL;
	int maxWordLength = getHeight();
	wordArray = new char[maxWordLength];

	return printAllWords(root, wordArray);		//Call primary (console) printAllWords function with default values
}

//Returns function call to primary printAllWords function with default values + prefix
//Parses TrieNode to print children from, string prefix (starting characters of word)
void Trie::printAllWords(TrieNode* root, string prefix) {
	//Dynamically initialise array with size of max length of string in dictionary
	char* wordArray = NULL;
	int maxWordLength = getHeight();
	wordArray = new char[maxWordLength];

	return printAllWords(root, wordArray, 0, prefix);		//Call primary (console) printAllWords function with default values + prefix
}

//Primary (console) printAllWords function
//Parses TrieNode to print children from, character array to store characters of word to be printed, position to insert character to character array, string prefix (starting characters of word) (if any)
void Trie::printAllWords(TrieNode* root, char* wordArray, int pos, string prefix) {
	//For empty trie
	if (root == NULL) {
		return;
	}

	//Base Case
	if (root->endOfWord) {
		printWord(wordArray, pos, prefix);									//Call helper function to print word to console
	}
	//Recursive step (Recur through every existing child until endOfWord flag is true)
	for (int i = 0; i < numberOfChar; i++) {
		if (root->children[i] != NULL) {
			wordArray[pos] = 'a' + i;										//Add character to character array
			printAllWords(root->children[i], wordArray, pos + 1, prefix);	//Recur to child nodes to complete word
		}
	}
}


//Functions used to print words in dictionary to external file

//Returns function call to primary (external file) printAllWords function with default values + destination file
//Parses destination file to save words to
void Trie::printAllWords(ofstream* destinationfile) {
	//Dynamically initialise array with size of max length of string in dictionary
	char* wordArray = NULL;
	int maxWordLength = getHeight();
	wordArray = new char[maxWordLength];

	return printAllWords(root, wordArray, destinationfile, 0);			//Call primary (external file) printAllWords function with default values + prefix
}

//Primary (external file) printAllWords function
//Parses TrieNode to start from, array of characters to store words, external file to save words to, position to insert charact to character array
void Trie::printAllWords(TrieNode* root, char* wordArray, ofstream* destinationfile, int pos) {
	//For empty trie
	if (root == NULL) {
		return;
	}

	//Base Case
	if (root->endOfWord) {
		printWord(wordArray, pos, destinationfile);									//Call helper function to print word to destination file
	}
	//Recursive step (Recur through every existing child until endOfWord flag is true)
	for (int i = 0; i < numberOfChar; i++) {
		if (root->children[i] != NULL) {
			wordArray[pos] = 'a' + i;												//Add character to character array
			printAllWords(root->children[i], wordArray, destinationfile, pos + 1);	//Recur to child nodes to complete word
		}
	}
}