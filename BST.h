//Citations: Stepik Module 5
//PowerPoint 4 - Balanced Trees
//https://www.tutorialspoint.com/cpp_standard_library/iomanip.htm

#pragma once
#include <iostream>
#include <queue>
#include <iomanip>
#ifndef BST_H
#define BST_H
using namespace std;

//create Binary Search Tree class
class BST
{
	//creates private variables
	private:
		//these vectors are used primarily for the printing functions as well as the search functions
		vector<int> vInOrder;
		vector<int> vPreOrder;
		vector<string> printInOrder;
		vector<string> printPostOrder;
		vector<string> printPreOrder;
		vector<string> printPreOrder2;
		struct TreeNode {
			//these are all properties of each node
			string name;
			int id;
			TreeNode* left;
			TreeNode* right;
			int height;
			//also creates constructor with two parameters, a string which would be the student name, and an id which is the UFID
			TreeNode(string n, int i) {
				name = n;
				id = i;
				left = nullptr;
				right = nullptr;
				height = 0;
			}
		};
		//sets the root of the tree to nullptr as well
		TreeNode* root = nullptr;
		
		//The rest of these functions are helper functions that will later be called in the public section
		//The reasoning for this is to be able to access the private variables

		//creates two temp nodes called node2 and node
		//sets node2 to the right of the current node
		//sets node to the left of the right of the current node
		//then sets the left of node2 to the current node (rotating left)
		//and lastly sets the right of the current node to the temp node (rotating left)
		TreeNode* leftRotation(TreeNode* tRoot) {
			TreeNode* node2 = tRoot->right;
			TreeNode* node = tRoot->right->left;
			node2->left = tRoot;
			tRoot->right = node;
			return node2;
		}
		//repeats the same process as last rotation but inversely. Basically every left becomes right and everything right becomes left
		TreeNode* rightRotation(TreeNode* tRoot) {
			TreeNode* node2 = tRoot->left;
			TreeNode* node = tRoot->left->right;
			node2->right = tRoot;
			tRoot->left = node;
			return node2;
		}
		//first rotates the right of the current node rightward then returns the left rotation of the current node
		TreeNode* rotateRightLeft(TreeNode* tRoot) {
			tRoot->right = rightRotation(tRoot->right);
			return leftRotation(tRoot);
		}
		//does the same as the last process but inversely
		TreeNode* rotateLeftRight(TreeNode* tRoot) {
			tRoot->left = leftRotation(tRoot->left);
			return rightRotation(tRoot);
		}
		
		//checks if the root (or current node) is nullptr
		//if so it inserts a new node with the name and id and prints successful.
		//lastly it returns the newly inserted node
		TreeNode* pInsert(TreeNode* pRoot, string name, int id) {
			if (pRoot == nullptr) {
				TreeNode* root = new TreeNode(name, id);
				cout << "successful" << endl;
				return root;
			}
			//if the ID that is trying to be inserted is less than the current node id
			//then it moves onto the left of the current node (because of how the BST works)
			else if (id < pRoot->id) {
				pRoot->left = pInsert(pRoot->left, name, id);
			}
			//checks if the ID trying to be inserted is greater than the current node id
			//then it moves onto the right of the current node (because of how the BST works)
			else if(id > pRoot->id) {
				pRoot->right = pInsert(pRoot->right, name, id);
			}
			//if none of the conditions are met meaning the id is equal to the current id
			//because the ids must be unique it prints unsuccessful
			else {
				cout << "unsuccessful" << endl;
			}
			
			//first calculates the balance factor of the current root
			pRoot->height = helpHeight(pRoot->left) - helpHeight(pRoot->right);
			//checks if  the balance factor is less than -1
			//if it is it checks if the balance factor of the right is greater than or less than 0
			//if greater than 0, performs the right left rotation and updates the height
			//else it performs a left rotation and updates the height
			if (pRoot->height < -1) {
				if (pRoot->right->height > 0) {
					pRoot = rotateRightLeft(pRoot);
					pRoot->height = helpHeight(pRoot->left) - helpHeight(pRoot->right);
				}
				else if(pRoot->right->height < 0) {
					pRoot = leftRotation(pRoot);
					pRoot->height = helpHeight(pRoot->left) - helpHeight(pRoot->right);
				}
			}
			//checks if the balance factor is greater than 1
			//if it is, it checks if the balance factor of the left is greater than or less than 0
			//if greater than 0, it performs a left right rotation and updates the height
			//else it performs a right rotation and updates the height
			else if (pRoot->height > 1) {
				if (pRoot->left->height < 0) {
					pRoot = rotateLeftRight(pRoot);
					pRoot->height = helpHeight(pRoot->left) - helpHeight(pRoot->right);
				}
				else if (pRoot->left->height > 0) {
					pRoot = rightRotation(pRoot);
					pRoot->height = helpHeight(pRoot->left) - helpHeight(pRoot->right);
				}
			}
			return pRoot;
		}
		
		//checks if the current node is nullptr which if not it moves on
		void pTraversing(TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			//pushes back the name of the current node to the string pre order vector
			printPreOrder.push_back(tRoot->name);
			//moves onto the left of the node
			pTraversing(tRoot->left);
			//moves onto the right of the node
			pTraversing(tRoot->right);
		}
		
		

		//does the same as the pTraversing(PreOrder) however it does so InOrder
		void inOrderTraversing(TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			inOrderTraversing(tRoot->left);
			printInOrder.push_back(tRoot->name);
			inOrderTraversing(tRoot->right);
		}

		//does the same as the pTraversing(PreOrder) however it does so PostOrder
		void postOrderTraversing(TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			postOrderTraversing(tRoot->left);
			postOrderTraversing(tRoot->right);
			printPostOrder.push_back(tRoot->name);
		}

		//Helper function that loops through the order vector and prints out each name seperated by commmas
		void helpTPre() {
			for (int i = 0; i < printPreOrder.size(); i++) {
				if (i != printPreOrder.size() - 1) {
					cout << printPreOrder[i] << ", ";
				}
				else {
					cout << printPreOrder[i] << endl;
				}
			}
		}
		
		//does the same as above but in order
		void helpTInOrder() {
			for (int i = 0; i < printInOrder.size(); i++) {
				if (i != printInOrder.size() - 1) {
					cout << printInOrder[i] << ", ";
				}
				else {
					cout << printInOrder[i] << endl;
				}
			}
		}

		//does the same as above but post order
		void helpTPost() {
			for (int i = 0; i < printPostOrder.size(); i++) {
				if (i != printPostOrder.size() - 1) {
					cout << printPostOrder[i] << ", ";
				}
				else {
					cout << printPostOrder[i] << endl;
				}
			}
		}

		//is a helper function that calculates the height of the current node
		int helpHeight(TreeNode* tRoot) {
			//sets height to 0 and initializes left and right height
			int height = 0;
			int leftHeight;
			int rightHeight;
			//checks if the node is nullptr in which case returns 0
			if (tRoot == nullptr) {
				return height;
			}
			//if not then it sets the left height to the left of the current node
			//sets the right height to the right of the current node
			//then sets the actual height to the max of the left or right height (adds by 1 for cases)
			else {
				leftHeight = helpHeight(tRoot->left);
				rightHeight = helpHeight(tRoot->right);
				height = max(leftHeight, rightHeight) + 1;
			}
			//returns the height
			return height;
		}

		//helper function for finding the level count
		void helpLevelCount(TreeNode* tRoot) {
			//checks if the root is nullptr in which case the tree is empty and returns 0
			if (tRoot == nullptr || tRoot == NULL) {
				cout << "0" << endl;
			}
			//if not then it finds the max height of the left subtree or the right subtree, adds it by 1, and prints it
			else {
				cout << max(helpHeight(tRoot->left), helpHeight(tRoot->right)) + 1 << endl;
			}
		}

		//checks if the current node is nullptr
		//if its not then it checks if the id is equal to the current node id
		//if it is it pushes back the name of the current node to the preOrder vector
		void helpSearch(int id, TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			if (id == tRoot->id) {
				printPreOrder.push_back(tRoot->name);
			}
			//moves onto the left and right of the current node
			helpSearch(id, tRoot->left);
			helpSearch(id, tRoot->right);
		}


		//does the same as search Id but for the name
		void helpSearchName(string name, TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			if (name == tRoot->name) {
				vPreOrder.push_back(tRoot->id);
			}
			helpSearchName(name, tRoot->left);
			helpSearchName(name, tRoot->right);
		}

		//finds the inOrder successor of the current node
		//basically goes as far down left as possible and when it reaches nullptr it returns the node before it
		TreeNode* helpInOrder(TreeNode* tRoot) {
			if (tRoot->left == nullptr) {
				return tRoot;
			}
			return helpInOrder(tRoot->left);
		}

		//a helper function to find the parent node of the node in the parameter
		TreeNode* findNode(int id, TreeNode* tRoot) {
			//if the node is nullptr it returns nullptr and prints unsuccessful
			if (tRoot == nullptr) {
				cout << "unsuccessful" << endl;
				return nullptr;
			}
			//if the root is attempting to be found, it'll return the root
			else if (tRoot->id == id) {
				return tRoot;
			}
			//if not it checks if the left id or the right id of the current node is equal to the id trying to be found
			else if ((tRoot->left != nullptr && tRoot->left->id == id) || (tRoot->right != nullptr && tRoot->right->id == id)) {
				return tRoot;
			}
			//if not then it checks if the id of the current node is greater than the id in the parameter
			//if it is it goes to the left of the root
			else if (tRoot->id > id) {
				return findNode(id, tRoot->left);
			}
			//otherwise it goes to the right of the root
			else {
				return findNode(id, tRoot->right);
			}
		}

		//this is a helper remove function that takes in the id of the node it wants to remove and the root
		void helpRemove(int id, TreeNode* pRoot) {
			//first uses the findNode function to find the node before the node it is looking to delete
			TreeNode* tRoot = findNode(id, pRoot);
			//checks if this node is nullptr
			if (tRoot == nullptr) {
				return;
			}
			//if not it checks if the id of the node is equal to the id it is passing, meaning that it is trying to remove the root
			else {
				if (tRoot->id == id) {
					//checks for the two children case
					if (tRoot->left != nullptr && tRoot->right != nullptr) {
						//sets temp to the inorder successor
						TreeNode* temp = helpInOrder(tRoot->right);
						//copys the data of the inorder successor
						string tempName = temp->name;
						int tempId = temp->id;
						//finds the node before the inorder successor
						TreeNode* tempNode = findNode(tempId, pRoot);
						//puts the data of the inorder successor into the root
						tRoot->name = tempName;
						tRoot->id = tempId;
						//checks to see which of the tempNode's children is the inOrder successor
						if (tempNode->left->id == tempId) {
							//if it is the left child it sets it to nullptr
							tempNode->left = nullptr;
						}
						else {
							//if not it sets the right of tempNode to the right of the inOrder successor to avoid loss of data
							if (temp->right != nullptr) {
								tempNode->right = temp->right;
							}
							else {
								//if not it sets the right to nullptr
								tempNode->right = nullptr;
							}

						}
						cout << "successful" << endl;

					}
					//then checks for the one child case
					//if a child exists it deletes the root and replaces it with the existing child
					else if (tRoot->left != nullptr) {
						TreeNode* temp = tRoot->left;
						TreeNode* temp2 = tRoot;
						delete temp2;
						tRoot = temp;
						cout << "successful" << endl;
					}
					//does the same as above but for the right side
					else if (tRoot->right != nullptr) {
						TreeNode* temp = tRoot->right;
						TreeNode* temp2 = tRoot;
						delete temp2;
						tRoot = temp;
						cout << "successful" << endl;
					}
					//if there are no children it deletes the root and sets it to NULL
					else {
						TreeNode* temp = tRoot;
						delete temp;
						this->root = nullptr;
						cout << "successful" << endl;
					}
				}
				//then the function moves onto the left child and checks if the left child is the node it is attempting to remove
				else if (tRoot->left != nullptr && tRoot->left->id == id) {
					//if it is it checks if the node attempting to be removed has two children
					if (tRoot->left->left != nullptr && tRoot->left->right != nullptr) {
						//if it does it repeats the same steps as the root two child case
						//it is using tRoot->left however because the case is testing if the left child is the node it is attempting to remove
						TreeNode* temp = helpInOrder(tRoot->left->right);
						string tempName = temp->name;
						int tempId = temp->id;
						TreeNode* tempNode = findNode(tempId, pRoot);
						tRoot->left->name = tempName;
						tRoot->left->id = tempId;
						if (tempNode->left->id == tempId) {
							tempNode->left = nullptr;
						}
						else {
							if (temp->right != nullptr) {
								tempNode->right = temp->right;
							}
							else {
								tempNode->right = nullptr;
							}
						}
						cout << "successful" << endl;
					}
					//does the same as the root one child case
					else if (tRoot->left->left != nullptr) {
						TreeNode* temp = tRoot->left->left;
						TreeNode* temp2 = tRoot->left;
						delete temp2;
						tRoot->left = temp;
						cout << "successful" << endl;
					}
					//does the same as the root one child case
					else if (tRoot->left->right != nullptr) {
						TreeNode* temp = tRoot->left->right;
						TreeNode* temp2 = tRoot->left;
						delete temp2;
						tRoot->left = temp;
						cout << "successful" << endl;
					}
					//does the same as the no child case
					else {
						TreeNode* temp = tRoot->left;
						delete temp;
						tRoot->left = nullptr;
						cout << "successful" << endl;
					}
				}
				//these conditions are the same as above except with the right child
				else if (tRoot->right->id == id) {
					if (tRoot->right->left != nullptr && tRoot->right->right != nullptr) {
						TreeNode* temp = helpInOrder(tRoot->right->right);
						string tempName = temp->name;
						int tempId = temp->id;
						TreeNode* tempNode = findNode(tempId, pRoot);
						tRoot->right->name = tempName;
						tRoot->right->id = tempId;
						if (tempNode->left->id == tempId) {
							tempNode->left = nullptr;
						}
						else {
							if (temp->right != nullptr) {
								tempNode->right = temp->right;
							}
							else {
								tempNode->right = nullptr;
							}
						}
						cout << "successful" << endl;
					}
					else if (tRoot->right->left != nullptr) {
						TreeNode* temp = tRoot->right->left;
						TreeNode* temp2 = tRoot->right;
						delete temp2;
						tRoot->right = temp;
						cout << "successful" << endl;
					}
					else if (tRoot->right->right != nullptr) {
						TreeNode* temp = tRoot->right->right;
						TreeNode* temp2 = tRoot->right;
						delete temp2;
						tRoot->right = temp;
						cout << "successful" << endl;
					}
					else {
						TreeNode* temp = tRoot->right;
						delete temp;
						tRoot->right = nullptr;
						cout << "successful" << endl;
					}
				}
			}
		}
		
		//a helper function used to store the ids of the tree in order in a vector
		void helpNInOrder(TreeNode* tRoot) {
			if (tRoot == nullptr) {
				return;
			}
			helpNInOrder(tRoot->left);
			vInOrder.push_back(tRoot->id);
			helpNInOrder(tRoot->right);
		}

		//goes through the vector used above to find the Nth node of the in order vector and removes it using the remove function
		void helpRemoveN(TreeNode* tRoot, int i) {
			helpNInOrder(tRoot);
			if (i > vInOrder.size() - 1 || i < 0) {
				cout << "unsuccessful" << endl;
			}
			else {
				helpRemove(vInOrder[i], tRoot);
			}
			
		}
		
	public:
		//calls the helper insert function and sets it equal to this->root
		void insert(string name, int id) {
			this->root = pInsert(this->root, name, id);
		}

		//first clears the preOrder array
		//then calls the search helper function and checks if the preOrder vector's size is == 0
		//if it is then print unsuccessful meaning the id was not found
		//if not then it prints the name matching the id
		void searchId(int id) {
			printPreOrder.clear();
			helpSearch(id, this->root);
			if (printPreOrder.size() == 0) {
				cout << "unsuccessful" << endl;
			}
			else {
				for (int i = 0; i < printPreOrder.size(); i++) {
					cout << printPreOrder[i] << endl;
				}
			}
			
		}

		//does the same as search id but for the name
		void searchName(string name) {
			vPreOrder.clear();
			helpSearchName(name, this->root);
			if (vPreOrder.size() == 0) {
				cout << "unsuccessful" << endl;
			}
			else {
				//when printing the id of the name, it uses setw and setfill to ensure that the id is printed as an eight digit id with leading zeros if needed
				for (int i = 0; i < vPreOrder.size(); i++) {
					cout << setw(8) << setfill('0') << vPreOrder[i] << endl;
				}
			}
		}

		//calls the helper remove function
		void remove(int id) {
			helpRemove(id, this->root);
		}
		
		//calls the helper pre order functions
		void traversePreOrder() {
			if (this->root == nullptr) {
				
			}
			else {
				pTraversing(this->root);
				helpTPre();
			}
		}

		//calls the helper in order functions
		void traverseInOrder() {
			if (this->root == nullptr) {
				
			}
			else {
				inOrderTraversing(this->root);
				helpTInOrder();
			}
		}
		
		//calls the helper post order functions
		void traversePostOrder() {
			if (this->root == nullptr) {
				
			}
			else {
				postOrderTraversing(this->root);
				helpTPost();
			}
		}

		//the next three functions are in case the print functions are called again and if so it just clears the used vector to ensure no duplicates
		void traversePreOrder2() {
			if (this->root == nullptr) {
				
			}
			else {
				printPreOrder.clear();
				pTraversing(this->root);
				helpTPre();
			}
		}

		void traverseInOrder2() {
			if (this->root == nullptr) {
				
			}
			else {
				printInOrder.clear();
				inOrderTraversing(this->root);
				helpTInOrder();
			}
		}

		void traversePostOrder2() {
			if (this->root == nullptr) {
				
			}
			else {
				printPostOrder.clear();
				postOrderTraversing(this->root);
				helpTInOrder();
			}
		}

		//sets int h to the height of the node
		void height() {
			int h = helpHeight(this->root);
		}
		
		//calls the helper remove nth in order function
		void removeN(int i) {
			vInOrder.clear();
			helpRemoveN(this->root, i);
		}

		//calls the helper level count function
		void levelCount() {
			helpLevelCount(this->root);
		}
};
#endif