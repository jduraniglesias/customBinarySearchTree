#include <iostream>
#include "Student.h"
using namespace std;

class TreeNode
{
private:
	Student student;
public:
	TreeNode* left;
	TreeNode* right;
	int height;


	TreeNode* node() {
		TreeNode* treeNode = new TreeNode();
		treeNode->left = NULL;
		treeNode->right = NULL;
		treeNode->height = 0;
	}

	TreeNode* insert(TreeNode* root, string n, int i) {
		if (root == nullptr) {
			TreeNode* newNode;
			newNode->student.setId(i);
			newNode->student.setName(n);
			return newNode;
		}
		else if (i < root->student.getId()) {
			root->left = insert(root->left, n, i);
		}
		else {
			root->right = insert(root->right, n, i);
		}
		return root;
	}

};


