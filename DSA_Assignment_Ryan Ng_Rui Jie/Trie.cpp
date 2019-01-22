#include "pch.h"
#include "Trie.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//Helper functions ------------------------------------
//Helper function to print words found
void printWord(char* str, int n) {
	for (int i = 0; i < n; i++) {
		cout << str[i];
	}
	cout << endl;
}
void printWord(char* str, int n, ofstream* destinationfile) {
	for (int i = 0; i < n; i++) {
		*destinationfile << str[i];
	}
	*destinationfile << endl;
}

//----------------------------------------------------

//Constructor
Trie::Trie() {
	//Create root trieNode
	root = new TrieNode();
	height = 0;
}

//Modify height of trie
void Trie::setHeight(int h) {
	height = h;
}
int Trie::getHeight() {
	return height;
}

//Search for a string in the trie
bool Trie::search(string target) {
	TrieNode* temp = root;

	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);

		if (temp->children[currentCharacter - 'a'] != NULL)
			temp = temp->children[currentCharacter - 'a'];
		else
			return false;
	}
	return temp->endOfWord;
}

//Insert a string into the trie
void Trie::insert(string target) {
	TrieNode* temp = root;

	//Set height of trie to longest word
	if (target.length() > getHeight()) {
		setHeight(target.length());
	}

	for (int i = 0; i < target.length(); i++) {
	char currentCharacter = tolower(target[i]);				//Convert char to lowercase

		//if (currentCharacter < 97)
		//	goto jmp;

		if (temp->children[currentCharacter - 'a'] == NULL) {	//Create new trieNode if it does not exist in trie
			TrieNode* newNode = new TrieNode();
			temp->children[currentCharacter - 'a'] = newNode;
		}

		temp = temp->children[currentCharacter - 'a'];			//Traverse to the next trie node
	}

	temp->endOfWord = true;										//Set endOfWord bool to true to indicate that the character completes the word
}

//Remove a string from the trie  (Recursively delete nodes from bottom of trie)
TrieNode* Trie::remove(string target) {
	return remove(root, target);
}
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

	//If character is not the prefix for another word && is not the end of a word
	if (isEmpty(root) && root->endOfWord == false) {
		delete root;
		root = NULL;
	}

	return root;
}

//Check if node has any children
bool Trie::isEmpty(TrieNode* root) {
	for (int i = 0; i < numberOfChar; i++) {
		if (root->children[i] != NULL) {
			return false;
		}
	}
	return true;
}

//Print all words in dictionary to console
void Trie::printAllWords() {
	//Dynamically initialise array with size of max length of string in dictionary
	char* wordArray = NULL;
	int maxWordLength = getHeight();
	wordArray = new char[maxWordLength];

	return printAllWords(root, wordArray);
}
void Trie::printAllWords(TrieNode* root, char* wordArray, int pos) {
	//For empty trie
	if (root == NULL) {
		return;
	}

	//Base Case
	if (root->endOfWord) {
		printWord(wordArray, pos);
	}
	//Recursive step (Recur through every existing child until endOfWord flag is true)
	for (int i = 0; i < numberOfChar; i++) {
		if (root->children[i] != NULL) {
			wordArray[pos] = 'a' + i;
			printAllWords(root->children[i], wordArray, pos + 1);
		}
	}
}

//Print all words in dictionary to new file
void Trie::printAllWords(ofstream* destinationfile) {
	//Dynamically initialise array with size of max length of string in dictionary
	char* wordArray = NULL;
	int maxWordLength = getHeight();
	wordArray = new char[maxWordLength];

	return printAllWords(root, wordArray, destinationfile, 0);
}
void Trie::printAllWords(TrieNode* root, char* wordArray, ofstream* destinationfile, int pos) {
	//For empty trie
	if (root == NULL) {
		return;
	}

	//Base Case
	if (root->endOfWord) {
		printWord(wordArray, pos, destinationfile);
	}
	//Recursive step (Recur through every existing child until endOfWord flag is true)
	for (int i = 0; i < numberOfChar; i++) {
		if (root->children[i] != NULL) {
			wordArray[pos] = 'a' + i;
			printAllWords(root->children[i], wordArray, destinationfile, pos + 1);
		}
	}
}