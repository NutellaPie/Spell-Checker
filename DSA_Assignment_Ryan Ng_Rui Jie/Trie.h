#pragma once
#include <string>
using namespace std;

const int numberOfChar = 26;

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
	TrieNode* root;
	int height;

public:
	//Constructor
	Trie();

	//Modify height of trie
	void setHeight(int h);
	int getHeight();

	//Insert a string into the trie
	void insert(string target);

	//Remove a string from the trie
	TrieNode* remove(string target);
	TrieNode* remove(TrieNode* root, string target, int level = 0);

	//Search for a string in the trie
	bool search(string target);

	//Check if node has any children
	bool isEmpty(TrieNode* root);

	//Print all words in dictionary recursively
	void printAllWords();
	void printAllWords(TrieNode* root, char* wordArray, int pos = 0);

};

