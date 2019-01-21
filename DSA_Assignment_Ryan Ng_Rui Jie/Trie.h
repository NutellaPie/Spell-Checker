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
	};

	TrieNode* root;

public:
	//Constructor
	Trie();

	//Insert a string into the trie
	void insert(string target);

	//Remove a string from the trie
	void remove(string target);

	//Search an item in the trie
	bool search(string target);
};

