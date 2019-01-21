#include "pch.h"
#include "Trie.h"
#include <string>

using namespace std;

//Constructor
Trie::Trie() {
	//Create root trieNode
	root = new TrieNode();
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

	for (int i = 0; i < target.length(); i++) {
		char currentCharacter = tolower(target[i]);				//Convert char to lowercase

		if (temp->children[currentCharacter - 'a'] == NULL) {	//Create new trieNode if it does not exist in trie
			TrieNode* newNode = new TrieNode();
			temp->children[currentCharacter - 'a'] = newNode;
		}

		temp = temp->children[currentCharacter - 'a'];			//Traverse to the next trie node
	}

	temp->endOfWord = true;										//Set endOfWord bool to true to indicate that the character completes the word
}

//Remove a string from the trie
void Trie::remove(string target) {

}