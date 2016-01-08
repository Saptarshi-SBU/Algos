/*--------------------------------------------------------------------------
 *
 * Binary Tree 
 *
 *
 *
 *-------------------------------------------------------------------------*/

#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

struct TreeNode {
	int data_;
	TreeNode *leftp_;
	TreeNode *rightp_;

	TreeNode(int data) : data_(data) {}
       ~TreeNode() {}
};

typedef struct TreeNode TreeNode;

class Tree {

	protected:
		
		void destroy_tree(TreeNode *nodep) {

			if (!nodep)
				return;	

			destroy_tree(nodep->leftp_);
			destroy_tree(nodep->rightp_);
			cout << nodep->data_ << "  "; 
			delete nodep;
		}
			

		void insert_leaf(TreeNode *nodep) {

			int found = 0;
			TreeNode *curr = rootp_;

			while (!found) {

				if (nodep->data_ < curr->data_)	{

					if (curr->leftp_) {
						curr = curr->leftp_;
					} else { 
						found = 1;
					    	curr->leftp_ = nodep;	
					}

				} else if (nodep->data_ > curr->data_) {
			
					if (curr->rightp_) {
						curr = curr->rightp_;
					} else { 
						found  = 1;
						curr->rightp_ = nodep;
					}
				}
			}

		}

		
		int insert_leaf(TreeNode *nodep, TreeNode *curr) {

			if (!curr) 
				return 1;

			if (nodep->data_ < curr->data_) {
				if (insert_leaf(nodep, curr->leftp_)) 
					curr->leftp_ = nodep;
			} else {
				if (insert_leaf(nodep, curr->rightp_)) 
					curr->rightp_ = nodep;
			}
			
			return 0;
		}
			
		
		int isBSTUtil(TreeNode *nodep, int low, int high) {

			if (!nodep)
				return 1;

			if ((nodep->data_ < high) && (nodep->data_ > low)) {
				return ((isBSTUtil(nodep->leftp_, low, nodep->data_)) * (isBSTUtil(nodep->rightp_, nodep->data_, high)));
			} else {
				return 0;
			}
		}
			
		void inorder_recursive(TreeNode *root) {

			if (!root)
				return;

			inorder_recursive(root->leftp_);
			cout << root->data_ << "  ";
			inorder_recursive(root->rightp_);
		}

		void preorder_recursive(TreeNode *root) {

			if (!root)
				return;

			cout << root->data_ << "  ";
			preorder_recursive(root->leftp_);
			preorder_recursive(root->rightp_);
		}

		void postorder_recursive(TreeNode *root) {

			if (!root)
				return;

			postorder_recursive(root->leftp_);
			postorder_recursive(root->rightp_);
			cout << root->data_ << "  ";
		}

		void inorder_iterative(TreeNode *root) {
			
			stack<TreeNode*> s;	
			TreeNode *curr = rootp_;

			while (curr) {

				if (curr->leftp_) {

					//
					// store inorder successor
					//	

					s.push(curr);
					curr = curr->leftp_;

				} else if (curr->rightp_) {

						//
						// visit inorder successor
						//	

						cout << curr->data_ << "  ";
						curr = curr->rightp_;
				} else {
					//
					// pop stack to get the inorder successors
					//	

					assert(s.size());
					for (curr = s.top(); s.size(); curr = s.top(), s.pop() ) {

						//
						// visit inorder successor
						//	

						cout << curr->data_ << "  ";
						if (curr->rightp_) 
							break;
					}

					if (curr->rightp_) 
						curr = curr->rightp_;
					else
					  curr = 0;	
				}		

			};

		}

		void preorder_iterative(TreeNode *root) {

		}

		void postorder_iterative(TreeNode *root) {

		}

	public :

		TreeNode *rootp_;

		Tree(int data) {

			rootp_ = new TreeNode(data);
			rootp_->leftp_ = rootp_->rightp_ = 0;
		}

	       ~Tree() {
			cout << "deleting tree\t:";
			destroy_tree(rootp_);
			rootp_ = 0;
			cout << endl;
		}

		void insert(int data) {

			TreeNode *nodep = new TreeNode(data);
			nodep->leftp_ = nodep->rightp_ = 0;
			insert_leaf(nodep);
		}

		int isBST() {

			int result = isBSTUtil(rootp_, INT_MIN, INT_MAX);
			return result;
		}

		enum TraversalType {

			INORDER_RECURSIVE,

			PREORDER_RECURSIVE,

			POSTORDER_RECURSIVE,

			INORDER_ITERATIVE,

			PREORDER_ITERATIVE,

			POSTORDER_ITERATIVE,

			INORDER_STACKLESS,	

			PREORDER_STACKLESS,	

			POSTORDER_STACKLESS,	
		};

		void traverse(TraversalType select) {

			switch (select) {
			
				case INORDER_RECURSIVE:
					cout << "inorder \t:";			
					inorder_recursive(rootp_);
					cout << endl;
					break;

				case INORDER_ITERATIVE:
					cout << "inorder \t:";			
					inorder_iterative(rootp_);
					cout << endl;
					break;

				case PREORDER_RECURSIVE:

					cout << "preorder\t:";			
					preorder_recursive(rootp_);
					cout << endl;
					break;

				case POSTORDER_RECURSIVE:
	
					cout << "postorder\t:";			
					postorder_recursive(rootp_);
					cout << endl;
					break;

				default :
	
					break;
			}

		}

};
			
int main(void) {

	Tree *tree = new Tree(100);
	tree->insert(50);
	tree->insert(200);
	tree->insert(25);
	tree->insert(150);
	tree->insert(250);
	tree->insert(80);
	tree->insert(75);
	cout << "Test BST\t:" << (tree->isBST() ? "True" : "False") << endl;
	tree->traverse(Tree::INORDER_RECURSIVE);
	tree->traverse(Tree::INORDER_ITERATIVE);
	tree->traverse(Tree::PREORDER_RECURSIVE);
	tree->traverse(Tree::POSTORDER_RECURSIVE);
	delete tree;
}
