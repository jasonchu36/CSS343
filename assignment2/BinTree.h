#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

class BinTree {				// you add class/method comments and assumptions

friend ostream& operator<<(ostream &out, const BinTree &bt);

public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();	
    							// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();
    						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;
    
	bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &) const;
		
	void bstreeToArray(NodeData *[]);
	void arrayToBSTree(NodeData *[]);

  int getHeight(const NodeData &) const;

  void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node 
  {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// utility functions
void inorderHelper(Node* ) const;

// Add more functions below as needed
void makeEmptyHelper(Node* &);
void assignHelper(Node*, Node* &);
bool equalityHelper(Node*, Node*) const;
bool insertHelper(Node*& , NodeData*);
bool retrieveHelper(Node* , const NodeData &, NodeData* &) const;
int bstreeToArrayHelper(Node*, NodeData* []);
void arrayToBSTreeHelper(Node *, NodeData* [], int, int);
int getHeightHelper(const NodeData&, Node*) const;
int recursiveHeightFinder(Node*) const;

void sideways(Node*, int) const;			// provided below, helper for displaySideways()
};

#endif //BINTREE_H