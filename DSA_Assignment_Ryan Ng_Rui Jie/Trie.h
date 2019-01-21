#pragma once
#include <string>
using namespace std;

const int numberOfChar = 26;

class Trie
{
private:
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

	TrieNode* root;

public:
	//Constructor
	Trie();

	//Insert a string into the trie
	void insert(string target);

	//Remove a string from the trie
	void remove(string target);

	//Search for a string in the trie
	bool search(string target);
};

