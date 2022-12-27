// ------------------------------------------------ BinTree.cpp -------------------------------------------------------
//
// Jason Chu CSS 343
// Created on 4/18/2022
// Last modification made on 4/24/2022
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To create a BST
// --------------------------------------------------------------------------------------------------------------------
// array size is assumed to be 100
// --------------------------------------------------------------------------------------------------------------------

#include "BinTree.h"

using namespace std;

// --------------------- Overloaded << --------------------------
// Displays data from the BSTree in order.
// --------------------------------------------------------------
ostream &operator<<(ostream &out, const BinTree &tree) 
{
  tree.inorderHelper(tree.root);
  out << endl;
  return out;
} // end of overloaded << function

// --------------------- Constructor ----------------------------
// Creates an empty tree
// --------------------------------------------------------------
BinTree::BinTree() 
{ 
  this->root = NULL; 
} // end of constructor

// -------------------- Copy Constructor ------------------------
// Creates a deep copy of another tree
// --------------------------------------------------------------
BinTree::BinTree(const BinTree &secondTree) 
{
  this->root = NULL;
  *this = secondTree;
} // end of copy constructor

// ---------------------- Destructor ----------------------------
// Calls makeEmpty() function to delete the entire BST
// --------------------------------------------------------------
BinTree::~BinTree() 
{ 
  this->makeEmpty(); 
} // end of destructor

// ----------------------- isEmpty() ----------------------------
// Tests if BST is empty
// --------------------------------------------------------------
bool BinTree::isEmpty() const 
{
  if (this->root == NULL) 
  {
    return true;
  }

  return false;
} // end of isEmpty()

// ---------------------- makeEmpty() ---------------------------
// Deletes the entire BST
// --------------------------------------------------------------
void BinTree::makeEmpty() 
{ 
  makeEmptyHelper(root); 
} // end of makeEmpty()

// -------------------- makeEmptyHelper -------------------------
// Helper function for makeEmpty() function
// --------------------------------------------------------------
void BinTree::makeEmptyHelper(Node *&current) 
{
  if (current == NULL)
  {
    return;
  }

  makeEmptyHelper(current->left);
  makeEmptyHelper(current->right);
  
  delete current->data;
  current->data = NULL;
  delete current;
  current = NULL;  
} // end of makeEmptyHelper()

// --------------------- Overloaded = ---------------------------
// Assigns one tree over the second tree
// --------------------------------------------------------------
BinTree &BinTree::operator=(const BinTree &secondTree) 
{
  if (*this == secondTree)
  {
    return *this;
  }
  
  this->makeEmpty();

  assignHelper(secondTree.root, this->root);

  return *this;
} // end of overloaded = function

// --------------------- assignHelper ---------------------------
// Helper function for overloaded = function
// --------------------------------------------------------------
void BinTree::assignHelper(Node *secondTree, Node *&firstTree) 
{
  if (secondTree == NULL) 
  {
    firstTree = NULL;
  }

  if (secondTree != NULL) 
  {
    firstTree = new Node;
    NodeData *temp = new NodeData(*secondTree->data);
    firstTree->data = temp;

    assignHelper(secondTree->left, firstTree->left);
    assignHelper(secondTree->right, firstTree->right);
  }  
} // end of assignHelper() function

// --------------------- Overloaded == --------------------------
// Tests if two trees are identical
// --------------------------------------------------------------
bool BinTree::operator==(const BinTree &secondTree) const 
{
  if (this->root == NULL && secondTree.root == NULL)
  {
    return true;
  }
  else
  {
    return equalityHelper(this->root, secondTree.root);
  }
} // end of overloaded == function

// --------------------- equalityHelper -------------------------
// Helper function for overloaded == operator function
// --------------------------------------------------------------
bool BinTree::equalityHelper(Node *firstTree, Node *secondTree) const 
{
  if (firstTree == NULL && secondTree == NULL) // checks if both trees are empty
  {
    return true;
  }

  if (firstTree == NULL || secondTree == NULL) // checks if one of the two trees are empty
  {
    return false;
  }
  
  if (firstTree != NULL && secondTree != NULL) // traverse through the tree as long as both trees are not empty
  {
    return (*firstTree->data == *secondTree->data &&
            equalityHelper(firstTree->left, secondTree->left) &&
            equalityHelper(firstTree->right, secondTree->right));
  }

  return false;
} // end of equalityHelper function

// --------------------- Overloaded != --------------------------
// Tests if two trees are not identical
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree &secondTree) const 
{
  return !(*this == secondTree);
} // end of overloaded != operator

// ------------------------- insert -----------------------------
// creates a new node and inserts data at new node
// --------------------------------------------------------------
bool BinTree::insert(NodeData *dataToInsert) 
{
  return insertHelper(this->root, dataToInsert);
} // end of insert function

// --------------------- insertHelper ---------------------------
// Helper function for insert function
// --------------------------------------------------------------
bool BinTree::insertHelper(Node *&current, NodeData *data) 
{
  if (current == NULL) 
  {
    current = new Node();
    current->data = data;
    current->left = NULL;
    current->right = NULL;
    return true;
  } 
  else if (*data < *current->data) 
  {
    return insertHelper(current->left, data);
  } 
  else if (*data > *current->data)
  {
    return insertHelper(current->right, data);
  } 
  return false;
} // end of insertHelper function

// ------------------------ retrieve ----------------------------
// Find data within a BST
// --------------------------------------------------------------
bool BinTree::retrieve(const NodeData &dataToRetrieve, NodeData* &retrieved) const 
{
  retrieveHelper(this->root, dataToRetrieve, retrieved);

  if (retrieved != NULL)
  {
    return true;
  }

  return false;
} // end of retrieve function

// --------------------- retrieveHelper -------------------------
// Helper function for retrieve function
// --------------------------------------------------------------
bool BinTree::retrieveHelper(Node* current, const NodeData &dataToRetrieve, NodeData* &retrieved) const 
{
  if (current == NULL) // checks for empty tree
  {
    retrieved = NULL;
    return false;
  }

  if (*current->data == dataToRetrieve) // if data is found
  {
    retrieved = current->data;
    return true;
  } 
  else if (*current->data < dataToRetrieve) // traverse right
  {
    retrieveHelper(current->right, dataToRetrieve, retrieved);
  } 
  else if (*current->data > dataToRetrieve) // traverse left
  {
    retrieveHelper(current->left, dataToRetrieve, retrieved);
  } 
  
  return false; // data not found
} // end of retrieveHelper function

// --------------------- bstreeToArray --------------------------
// Creates a sorted array from a BST
// --------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arrayToFill[])
{
  bstreeToArrayHelper(this->root, arrayToFill);

  this->makeEmpty();
} // end of bstreeToArray function

// ------------------ bstreeToArrayHelper -----------------------
// Displays data from the BSTree in order.
// --------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* current, NodeData* toFill[])
{
  if (current == NULL)
  {
      return 0;  
  }

  int left = bstreeToArrayHelper(current->left, toFill);

  NodeData *temp;
  temp = current->data; 
  current->data = NULL; 
  *(toFill + left) = temp;
  temp = NULL;

  int right = bstreeToArrayHelper(current->right, toFill + left + 1);

  return left + right + 1;
} // end of bstreeToArrayHelper function

// --------------------- arrayToBSTree --------------------------
// Creates a balanced BST from a sorted array
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* source[])
{
this->makeEmpty(); 

int high = 0;

for(int i = 0; i < 100; i++)    
{
  if (source[i] != NULL)
  {
    high++; 
  }
  else
  {
    source[i] = NULL;
  }
}

  arrayToBSTreeHelper(root, source, 0, high-1);
} // end of arrayToBSTree function

// ------------------ arrayToBSTreeHelper -----------------------
// Helper function for arrayToBSTree function
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node *current, NodeData* source[], int start, int end)
{
  if (start > end)
  {
    current = NULL; 
  }
  else
  {
    int mid = (start + end) / 2;

    NodeData* temp; 
    temp = source[mid];   
    source[mid] = NULL;   

    insert(temp);   
    arrayToBSTreeHelper(current, source, start, mid - 1);    
    arrayToBSTreeHelper(current, source, mid + 1, end);   
  }
} // end of arrayToBSTreeHelper function

// ----------------------- getHeight ----------------------------
// Finds the height of a node
// --------------------------------------------------------------
int BinTree::getHeight(const NodeData &nodeToFind) const 
{
  return getHeightHelper(nodeToFind, this->root);
} // end of getHeight function

// -------------------- getHeightHelper -------------------------
// Helper function for getHeight function
// --------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData &nodeToFind, Node *current) const 
{
  if (current == NULL) 
  {
    return 0;
  } 
  else if (*current->data == nodeToFind) 
  {
    return recursiveHeightFinder(current);
  } 
  else 
  {
    int left = getHeightHelper(nodeToFind, current->left);
    int right = getHeightHelper(nodeToFind, current->right);

    return (left < right) ? right : left;
  }
} // end of getHeightHelper function

// ---------------- recursiveHeightFinder -----------------------
// Calculates the height of a node
// --------------------------------------------------------------
int BinTree::recursiveHeightFinder(Node *current) const 
{
  if (current == NULL) {
    return 0;
  } 
  else 
  {
    int left = recursiveHeightFinder(current->left);
    int right = recursiveHeightFinder(current->right);

    if (left > right) 
    {
      return 1 + left;
    }

    return 1 + right;
  }
} // end of recursiveHeightFinder function

// helper function to print data nodes through in-order traversal
void BinTree::inorderHelper(Node *current) const 
{
  if (current != NULL) {
    inorderHelper(current->left);
    cout << *current->data << " ";
    inorderHelper(current->right);
  }
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const 
{
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}