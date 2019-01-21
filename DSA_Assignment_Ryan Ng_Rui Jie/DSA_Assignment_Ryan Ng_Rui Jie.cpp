#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

int option;

void Menu();

int main()
{
	Trie test;

	test.insert("car");
	test.insert("cars");
	cout << test.search("ca");
	//while (true) {

	//	Menu();

	//	switch (option) {
	//	case 1:
	//		break;
	//	case 2:
	//		break;
	//	case 3:
	//		break;
	//	case 4:
	//		break;
	//	case 5:
	//		break;
	//	case 0:
	//		cout << "Bye!" << endl;
	//		system("PAUSE");
	//		return 0;
	//	}
	//}
}

void Menu() {
	cout << endl << "---------------- Spell Checker -------------------" << endl;
	cout << "[1] Spell Check a Word" << endl;
	cout << "[2] Spell Check a File" << endl;
	cout << "[3] Add a New Word to the Dictionary" << endl;
	cout << "[4] Save the Dictionary (With New Words Added)" << endl;
	cout << "[5] Display All Words in the Dictionary that Starts with a Certain Letter" << endl;
	cout << "[0] Exit " << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Enter your option : ";

	cin >> option;

	cout << endl;
}