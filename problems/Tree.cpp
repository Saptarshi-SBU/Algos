/*--------------------------------------------------------------------------
 *
 * Binary Tree 
 *
 * g++ -g -DDEBUG -o tree Tree.cpp
 *
 *-------------------------------------------------------------------------*/

#include <iostream>
#include <cassert>
#include <stack>
#include <queue>
#include <climits>

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
			bool done = false;
			stack<TreeNode*> s;	
			TreeNode *curr = rootp_;

			while (!done) {

				//
				// store inorder predecessor
				//	

				s.push(curr);

				if (curr->leftp_) {

					curr = curr->leftp_;

				} else if (curr->rightp_) {

					s.pop();

					//
					// visit inorder successor
					//	
					cout << curr->data_ << "  ";

					curr = curr->rightp_;

				} else {
					//
					// pop stack to get the inorder successors
					//	

					while(s.size()) {

						curr = s.top();
						s.pop();

						//
						// visit inorder successor
						//	

						cout << curr->data_ << "  ";

						if (curr->rightp_) 
							break;
					};

					if (curr->rightp_)
						curr = curr->rightp_;
					else
						done = true;
				}
			
			};

		}

		void preorder_iterative(TreeNode *root) {

			bool done = false;

			stack<TreeNode *> s;

			TreeNode *curr = rootp_;
			
			while (!done) {

				//
				// Visit	
				//
				
				cout << curr->data_ << "  ";

				if ((curr->leftp_) && (curr->rightp_)) {

					//
					// Store PreOrder Successor	
					//

					s.push(curr->rightp_);

					curr = curr->leftp_;

				} else if (curr->leftp_) {

					curr = curr->leftp_;

				} else if (curr->rightp_) {

					curr = curr->rightp_;

				} else {

					//
					// Pop PreOrder Successor
					//

					if (s.size()) {
						curr = s.top();
						s.pop();
					} else {
						done = true;
					}
				}
			};
		}

		void postorder_iterative(TreeNode *root) {

			stack<TreeNode *> ps, cs;

			TreeNode *curr = rootp_;

			cs.push(curr);

			while (cs.size()) {
			
				curr = cs.top();

				cs.pop();

				ps.push(curr);

				if (curr->leftp_)
					cs.push(curr->leftp_);

				if (curr->rightp_)
					cs.push(curr->rightp_);
				
			};	

			while (ps.size()) {

				curr = ps.top();

				ps.pop();

				cout << curr->data_ << "  ";
			};

		}

		void inorder_stackless(TreeNode *root) {

			TreeNode *curr = rootp_;

			TreeNode *temp = 0;

			while (curr) {

				if (curr->leftp_) {

					//
					//	Check if node threaded
					//

					temp = curr->leftp_;

					while (temp->rightp_) {
						if (temp->rightp_ == curr) 
							break;
						temp = temp->rightp_;
					};

					//
					//	thread/dethread
					//

					if (!temp->rightp_) {

						// down
						
						temp->rightp_ = curr;
						curr = curr->leftp_;	
					} else  {

						//up
						
						temp->rightp_ = 0;
						cout << curr->data_ << "  ";
						curr = curr->rightp_;  
					}
						
						
				} else if (curr->rightp_) {

					//
					//	inorder sucessor
					//					
					//

					cout << curr->data_ << "  ";

					curr = curr->rightp_;

				} else {

					//
					// rightmost
					//
					cout << curr->data_ << endl;
					break;
				}
					
			};



		}

		void preorder_stackless(TreeNode *root) {
			
			TreeNode *curr = rootp_;

			TreeNode *temp = 0;

			while (curr) {


				if (curr->leftp_) {

					//
					//	Check if node threaded
					//

					temp = curr->leftp_;

					while (temp->rightp_) {
						if (temp->rightp_ == curr) 
							break;
						temp = temp->rightp_;
					};

					//
					//	thread/dethread
					//

					if (!temp->rightp_) {

						// down
						
						temp->rightp_ = curr;

						cout << curr->data_ << "  ";
						curr = curr->leftp_;	

					} else  {

						//up
						
						temp->rightp_ = 0;
						curr = curr->rightp_;  
					}
						
				} else if (curr->rightp_) {

					//
					//	inorder sucessor
					//					
					//

					cout << curr->data_ << "  ";

					curr = curr->rightp_;

				} else {

					//
					// rightmost
					//
					cout << curr->data_ << endl;
					break;
				}
			};

		}

		void postorder_stackless(TreeNode *root) {

			TreeNode *curr = rootp_;

			TreeNode *temp = 0;

			while (curr) {
			
				if (curr->rightp_) {

					temp = curr->rightp_;

					while (temp->leftp_) {
						if (temp->leftp_ == curr)
							break;
						temp = temp->leftp_;
					}
				
					if (!temp->leftp_) {
						// Down
						temp->leftp_ = curr;
						cout << curr->data_ << "  ";
						curr = curr->rightp_;
					} else {
						// Up
						temp->leftp_ = 0;
						curr = curr->leftp_;
					}

				} else if (curr->leftp_) {

					cout << curr->data_ << "  ";
					curr = curr->leftp_;

				} else {
					
					cout << curr->data_ << "  ";
					break;
				}			
			};

		}


		void serializeBSTUtil(TreeNode *root, queue<int>& q) {

			if (!root) 
				return;

			q.push(root->data_);
			serializeBSTUtil(root->leftp_, q);
			serializeBSTUtil(root->rightp_, q);
			return;
		}


		TreeNode* deserializeBSTUtil(int low, int high, queue <int>& q) {

			int key;

			TreeNode *nodep = 0;

			if (q.size())
				return 0;

			key = q.front();

			if ((key < high) && (key > low)) {

				q.pop();
				nodep = new TreeNode(key);
				nodep->leftp_  = deserializeBSTUtil(low, nodep->data_, q);
				nodep->rightp_ = deserializeBSTUtil(nodep->data_, high, q);
			}

			return nodep;

		}
			 
	public :

		TreeNode *rootp_;

		Tree(int data) {

			rootp_ = new TreeNode(data);
			rootp_->leftp_ = rootp_->rightp_ = 0;
		}

	       ~Tree() {
			cout << "\ndeleting tree\t:";
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
				case INORDER_STACKLESS:
					cout << "inorder \t:";			
					inorder_stackless(rootp_);
					cout << endl;
					break;

				case PREORDER_RECURSIVE:
					cout << "preorder\t:";			
					preorder_recursive(rootp_);
					cout << endl;
					break;

				case PREORDER_ITERATIVE:
					cout << "preorder \t:";			
					preorder_iterative(rootp_);
					cout << endl;
					break;

				case PREORDER_STACKLESS:
					cout << "preorder \t:";			
					preorder_stackless(rootp_);
					cout << endl;
					break;

				case POSTORDER_RECURSIVE:
					cout << "postorder\t:";			
					postorder_recursive(rootp_);
					cout << endl;
					break;

				case POSTORDER_ITERATIVE:
					cout << "postorder\t:";			
					postorder_iterative(rootp_);
					cout << endl;
					break;

				case POSTORDER_STACKLESS:
					cout << "postorder\t:";			
					postorder_stackless(rootp_);
					cout << endl;
					break;

				default :
	
					break;
			}

		}

	
		queue<int> serializeBST() {
				queue<int> q;

				serializeBSTUtil(rootp_, q);

				#if DEBUG
				queue<int> qdbg = q;

				cout << "serialize\t:";
				while (qdbg.size()) {
					cout << qdbg.front() << "  ";
					qdbg.pop();
				}
				cout << endl;
				#endif

				return q;
		}

		TreeNode* deserializeBST(queue<int>& q) {
		
				TreeNode *rootp;

				rootp = deserializeBSTUtil(INT_MIN, INT_MAX, q);

				#if DEBUG
				cout << "deserialize\t:";			
				preorder_iterative(rootp);		
				cout << endl;
				#endif

				return rootp;
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
	tree->traverse(Tree::INORDER_STACKLESS);
	tree->traverse(Tree::PREORDER_RECURSIVE);
	tree->traverse(Tree::PREORDER_ITERATIVE);
	tree->traverse(Tree::PREORDER_STACKLESS);
	tree->traverse(Tree::POSTORDER_RECURSIVE);
	tree->traverse(Tree::POSTORDER_ITERATIVE);
	tree->traverse(Tree::POSTORDER_STACKLESS);
	queue<int> q = tree->serializeBST();
	tree->deserializeBST(q);
	delete tree;
}
