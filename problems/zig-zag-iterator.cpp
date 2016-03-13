/*--------------------------------------------------------------------------
 *
 * Binary Tree 
 *
 * g++ -g -DDEBUG -o tree Tree.cpp
 *
 *  03/13/2016 :  Use of two stacks + use of flags to switch
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
			insert_leaf(nodep, rootp_);
		}
		
		void destroy(void) {
			destroy_tree(rootp_);
		}

		
};
		
class ZigZagIterator {
		
		stack<TreeNode *> p;
		stack<TreeNode *> q;

		bool pFlag = false;
		bool qFlag = false;

	public :
		ZigZagIterator(TreeNode *rootp) {
			if (rootp)
				p.push(rootp);
			pFlag = true;
		}

		bool hasNext(void) {
			if (p.empty() && q.empty())
				return false;
			else
				return true;
		}

		int next(void) {
			TreeNode *curr = NULL;
			
			if (!p.empty() && pFlag) {
				curr = p.top();
				p.pop();
				if (curr->rightp_)
					q.push(curr->rightp_);
				if (curr->leftp_)
					q.push(curr->leftp_);
				if (p.empty()) {
					qFlag = true;
					pFlag = false;
				}
			} else if (!q.empty() && qFlag) {
				curr = q.top();
				q.pop();
				if (curr->leftp_)
					p.push(curr->leftp_);
				if (curr->rightp_)
					p.push(curr->rightp_);
				if (q.empty()) {
					pFlag = true;
					qFlag = false;
				}
			}
			
			if (curr)
				return curr->data_;
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
	tree->insert(20);
	tree->insert(15);
	tree->insert(10);
	tree->insert(5);
	tree->insert(400);
	
	ZigZagIterator *i = new ZigZagIterator(tree->rootp_);
	while (i->hasNext())
		cout << i->next() << endl;
	delete i;
	delete tree;
	return 0;
}
