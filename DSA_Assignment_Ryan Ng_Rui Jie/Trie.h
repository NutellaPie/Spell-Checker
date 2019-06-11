#pragma once
#include <string>
using namespace std;

const int numberOfChar = 26;	//Maximum number of different characters allowed to store in the trie (26 characters in the english alphabet)

struct TrieNode {
	TrieNode* children[numberOfChar];
	bool endOfWord;

	//Trie node constructor
	TrieNode() {

		//Initialise array with NULLs
		for (int i = 0; i < numberOfChar; i++) {
			children[i] = NULL;
		}

		//Set end of word to false
		endOfWord = false;
	}
};

class Trie
{
private:
	//Trie class properties
	TrieNode* root;
	int height;

public:
	//Trie Constructor
	Trie();

	//Function used to set the height property of the trie
	//Parses an integer height
	void setHeight(int h);

	//Function used to get the height property of the trie
	//Returns the height of the trie as an integer
	int getHeight();

	//Function used to insert a string into the trie
	//Parses a string to be inserted into the trie
	void insert(string target);


	//Functions used to remove a string from the trie (Recursively delete nodes from bottom of trie)

	//Returns function call to primary remove function with default values
	//Parses string to be removed	
	TrieNode* remove(string target);

	//Primary remove function
	//Returns a TrieNode to be used to recursively delete nodes
	//Parses trienode to start from, string to be removed, current depth of trie
	TrieNode* remove(TrieNode* root, string target, int level = 0);

	//Function used to search for a string in the trie
	//Returns a boolean value of true if string exists in the trie and false if it does not
	//Parses a string to be searched in the trie
	bool search(string target);

	//Function used to check if trie has any children
	//Returns a boolean value of true if there is no children and false if it has children
	//Parses TrieNode pointer to be checked	
	bool isEmpty(TrieNode* root);

	//Function used to return a pointer to a particular TrieNode
	//Returns a pointer to a specified TrieNode within the trie (Return's NULL if target does not exist)
	//Parses a string to traverse through
	TrieNode* getNode(string target);


	//Functions used to print words in dictionary to console

	//Returns function call to primary (console) printAllWords function with default values
	void printAllWords();

	//Returns function call to primary printAllWords function with default values + prefix
	//Parses TrieNode to print children from, string prefix (starting characters of word)
	void printAllWords(TrieNode* root, string prefix = "");

	//Primary (console) printAllWords function
	//Parses TrieNode to print children from, character array to store characters of word to be printed, position to insert character to character array, string prefix (starting characters of word) (if any)
	void printAllWords(TrieNode* root, char* wordArray, int pos = 0, string prefix = "");

	
	//Functions used to print words in dictionary to external file
	
	//Returns function call to primary (external file) printAllWords function with default values + destination file
	//Parses destination file to save words to
	void printAllWords(ofstream* destinationfile);
	
	//Primary (external file) printAllWords function
	//Parses TrieNode to start from, array of characters to store words, external file to save words to, position to insert charact to character array
	void printAllWords(TrieNode* root, char* wordArray, ofstream* destinationfile, int pos = 0);
};

