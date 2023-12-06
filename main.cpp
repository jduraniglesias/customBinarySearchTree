#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BST.h"
using namespace std;

//a helper function to remove the spaces in a string
//basically loops through the string and checks if each char != ' '. if its not it adds it to the temp string and returns the new string
string removeSpace(string str, char space) {
	string temp = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != space) {
			temp = temp + str[i];
		}
	}
	str = temp;
	return str;
}

int main()
{
	BST newTree;
	string line;
	string operation;
	string id;
	string name;
	char test = '"';

	//strings of the commands to check which command is being executed
	string op1 = "insert";
	string op2 = "search";
	string op3 = "remove";
	string op4 = "printInorder";
	string op5 = "printPreorder";
	string op6 = "printPostorder";
	string op7 = "printLevelCount";
	string op8 = "removeInorder";
	
	//checking ints to check if one of the printing functions has been used
	int checkTO = 0;
	int checkTP = 0;
	int checkTP2 = 0;

	//takes in the number of commands needed
	int commands;
	cin >> commands;
	int i = 0;

	//while loop reading the line and storing each word or number into its own variable and also checking the number of commands
	while (getline(cin, line) && i <= commands) {
		stringstream sstream(line);
		//uses .find to check if the line contains a name
		if (line.find(test) != string::npos) {
			getline(sstream, operation, '"');
			getline(sstream, name, '"');
			getline(sstream, id);
			operation = removeSpace(operation, ' ');
			id = removeSpace(id, ' ');
			int newId;
			//checks if the id is empty and if not it converts it to an int
			//checks which command is being called
			if (operation == op1) {
				if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
					cout << "unsuccessful" << endl;
				}
				else if (id.length() != 8) {
					cout << "unsuccessful" << endl;
				}
				else if (id.find_first_not_of("1234567890") != string::npos) {
					cout << "unsuccessful" << endl;
				}
				else {
					if (id.empty() != true) {
						newId = stoi(id);
					}
					newTree.insert(name, newId);
				}
			}
			else if (operation == op2) {
				newTree.searchName(name);
			}
			
		}
		//if there are no names in the command then it does the same as above just checking for other commands
		else {
			getline(sstream, operation, ' ');
			getline(sstream, id);
			id = removeSpace(id, ' ');
			int newId;
			if (id.empty() != true) {
				if (id.find_first_not_of("1234567890") != string::npos) {
					operation = "";
				}
				else {
					newId = stoi(id);
				}
			}
			if (operation == op3) {
				if (id.length() != 8) {
					cout << "unsuccessful" << endl;
				}
				else {
					newTree.remove(newId);
				}
			}
			else if (operation == op2) {
				if (id.length() != 8) {
					cout << "unsuccessful" << endl;
				}
				else {
					newTree.searchId(newId);
				}
			}
			//checks if the traversals have been used once and if not then it adds it by 1
			else if (operation == op4) {
				if (checkTO == 0) {
					newTree.traverseInOrder();
					checkTO++;
				}
				else {
					newTree.traverseInOrder2();
				}
			}
			else if (operation == op5) {
				if (checkTP == 0) {
					newTree.traversePreOrder();
					checkTP++;
				}
				else {
					newTree.traversePreOrder2();
				}
				
			}
			else if (operation == op6) {
				if (checkTP2 == 0) {
					newTree.traversePostOrder();
					checkTP2++;
				}
				else {
					newTree.traversePostOrder2();
				}
				
			}
			else if (operation == op7) {
				newTree.levelCount();
			}
			else if (operation == op8) {
				newTree.removeN(newId);
			}
			else if (i != 0) {
				cout << "unsuccessful" << endl;
			}
		}
		//increments i which is counting the commands used
		i++;
	}

	return 0;
}

