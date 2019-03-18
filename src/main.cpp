#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#define pow2(n) (1 << (n))

using namespace std;

//Node struct
struct Node
{
  int data;
  struct Node *left;
	struct Node *right;

}*root;

//Linked list declaration
class LinkedList
{
public:
	Node* current;
	Node* root;

	LinkedList();
	~LinkedList();

	ifstream inFile;
	ofstream outFile;

  int height(Node *); 
  int diff(Node *);
  void display(Node *, int);
	void insert (int data);

	Node* create(int data);

  Node *rr_rotation(Node *); 
  Node *ll_rotation(Node *);
  Node *lr_rotation(Node *);
  Node *rl_rotation(Node *);
	
  Node* balance(Node *);
  Node* insert(Node *, int);
	
  void preorderTrav();
	void postorderTrav();
	void inorderTrav();
	void preorder(Node* p);
	void postorder(Node* p);
	void inorder(Node* p);
	void setRoot();
	int find(int data);
};

int main()
{
	LinkedList();
	ifstream inFile;
	inFile.open("lots_ints.txt");
	LinkedList l;
  int choice, item;

  while (1)
	{	cout << "1.Insert Element into the tree." << endl;
		cout << "2.Insert list of ints from text file" << endl;
		cout << "3.Display Balanced AVL Tree" << endl;
		cout << "4.InOrder traversal" << endl;
		cout << "5.PreOrder traversal" << endl;
		cout << "6.PostOrder traversal" << endl;
		cout << "6.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter value to be inserted: ";
			cin >> item;
			root = l.insert(root, item);
			break;
		//TODO: Loop through all numbers in lots_ints.txt
		// and import those ints into the tree.
		case 2: {
			int count;
			string  str;
			while (getline(inFile, str))
			{
				int iStr = std::stoi(str);
				root = l.insert(root,str)
			};
			break;}
		case 3:
			if (root == NULL)
			{
				cout << "Tree is Empty" << endl;
				continue;
			}
			cout << "Balanced AVL Tree:" << endl;
			l.display(root, 1);
			break;
		case 4:
			cout << "Inorder Traversal:" << endl;
			l.inorder(root);
			cout << endl;
			break;
		case 5:
			cout << "Preorder Traversal:" << endl;
			l.preorder(root);
			cout << endl;
			break;
		case 6:
			cout << "Postorder Traversal:" << endl;
			l.postorder(root);
			cout << endl;
			break;
		case 7:
			exit(1);
			break;
		default:
			cout << "Wrong Choice" << endl;
		}
	}
	inFile.close();
    return 0;
}

LinkedList::LinkedList()
{
	root = NULL;
}

LinkedList::~LinkedList()
{
}

Node* LinkedList::create(int data)
{
	Node* n = new Node;
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

Node *LinkedList::insert(Node *root, int value)
{
	if (root == NULL)
	{
		root = new Node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}
//Preorder
void LinkedList::preorderTrav()
{
	if (root){
		outFile.open("preorder.txt");
		preorder(root);
		outFile.close();
	}
}

void LinkedList::preorder(Node* p)
{
if (p != NULL){
cout << p->data << endl;
outFile << p->data << endl;
preorder(p->left);
preorder(p->right);
}
}
//PostOrder
void LinkedList::postorderTrav()
{
	if (root){
		outFile.open("postorder.txt");
		postorder(root);
		outFile.close();
	}
}
void LinkedList::postorder(Node* p)
{
if (p != NULL){
postorder(p->left);
postorder(p->right);
cout << p->data << endl;
outFile << p->data << endl;
}
}
//InOrder
void LinkedList::inorderTrav()
{
	if (root){
		outFile.open("inorder.txt");
		inorder(root);
		outFile.close();
	}
}

void LinkedList::inorder(Node* p)
{
if (p !=NULL){
inorder(p->left);
cout << p->data << endl;
outFile << p->data << endl;
inorder(p->right);
}
}

void LinkedList::setRoot()
{
	current = root;
}

int LinkedList::find(int q)
{
	//Returns a warning on my particular compiler but still compiles. 
	//Because the default state of the root's data IS NULL, this comparison must take place. I don't want to check and see if the root itself is null, which would clear the exception, because the root is created in the constructor and SHOULD be present with an empty data field.
	if (root->data == NULL) {
		cout << "There is no list" << endl;
		return 1;
	}
	else if (q == current->data) {
		cout << "Search query found" << endl;
		return q;
	}
	else if (q < current->data) {
		if (current->left != NULL) {
			cout << q << " is less than " << current->data << ". Traversing left." << endl;
			current = current->left;
			find(q);
			return q;
		}
		else {
			cout << "Search query not found" << endl;
			return 1;
		}
	}
	else if (q > current->data) {
		if (current->right != NULL) {
			cout << q << " is greater than " << current->data << ". Traversing right." << endl;
			current = current->right;
			find(q);
			return q;
		}
		else {
			cout << "Search query not found" << endl;
			return 1;
		}
	}
	else {
		cout << "Error" << endl;
		return 1;
	}

}

//Displays the avl tree in a graphical format
//A: Find a way to use tabs and spaces in order to structure the tree in a graphical format.
void LinkedList::display(Node *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}

//Finds the height of the tree.
//A: Find the height,
int LinkedList::height(Node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
//Finds the height difference of nodes in the tree.
int LinkedList::diff(Node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
 * Balancing AVL Tree
 */

 /*
 Create a balance factor based on the difference of the heights of children
 If it needs to be balanced, find the correct rotations on order to balance it.
 */
 
Node *LinkedList::balance(Node *temp)
{
	int bal_factor = diff(temp);
  //Right subtree is first, because I felt like it.
  //Positive difference values are the right subtree.
  //Negative difference values are the left subtree.

	if (bal_factor > 1) //If the right subtree is unbalanced.
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1) //If the left subtree is unbalanced.
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}


//////////////////
// ROTATIONS /////
//////////////////
/*

Rotate right - Actually a double right, because new root and it's right child needs to be rotated right. 

Rotate left  - Actually a double left, because new root and it's left child needs to be rotated left.

Left - Right rotation - Rotate right child left, then rotate it's parent right.

Right - Left, ^ vice versa.

*/

/*
 * Right- Right Rotation
 */
Node *LinkedList::rr_rotation(Node *parent)
{
	Node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

/*
 * Left- Left Rotation
 */
Node *LinkedList::ll_rotation(Node *parent)
{
	Node *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
 * Left - Right Rotation
 */
Node *LinkedList::lr_rotation(Node *parent)
{
	Node *temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
 * Right- Left Rotation
 */
Node *LinkedList::rl_rotation(Node *parent)
{
	Node *temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}