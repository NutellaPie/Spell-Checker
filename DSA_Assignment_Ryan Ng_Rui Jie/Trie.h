#pragma once
#include <iostream>
#include <string>
using namespace std;

class Trie
{
	struct TrieNode {
		TrieNode* children[26];
		bool endOfWord;
	};

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

