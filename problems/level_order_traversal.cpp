/*--------------------------------------------------------------------------
 *
 *  recover BST 
 *
 *  g++ -g -DDEBUG -o tree recover_bst.cpp
 *
 *  03/13/2016 :  
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

class Solution {

    queue<TreeNode *> p;
    queue<TreeNode *> q;

    bool pflag = false;
    bool qflag = false;

    vector<vector<int>> v;

public:

    vector<vector<int>> levelOrder(TreeNode* root) {

        if (!root)
            return v;

        vector<int> vec;
        q.push(root);
	qflag = true; 

        while (!q.empty() || !p.empty()) {

            while (!q.empty() && qflag) {

                root = q.front();
                q.pop();

                vec.push_back(root->data_);

                if (root->leftp_)
                    p.push(root->leftp_);

                if (root->rightp_)
                    p.push(root->rightp_);

                if (q.empty()) {
                    qflag = false;
                    pflag = true;
                }    
            }

	    if (!vec.empty()) {
            	v.push_back(vec);
            	vec.clear();
	    }	

            while (!p.empty() && pflag) {

                root = p.front();
                p.pop();
                
                vec.push_back(root->data_);

                if (root->leftp_)
                    q.push(root->leftp_);

                if (root->rightp_)
                    q.push(root->rightp_);

                if (p.empty()) {
                    pflag = false;
                    qflag = true;
                }    

            }

	    if (!vec.empty()) {
            	v.push_back(vec);
            	vec.clear();
	    }	
        }

        return v;
    }

};	


int main(void) {

	Tree *tree = new Tree(1);
	tree->insert(3);
	tree->insert(2);
	Solution *sol = new Solution();
	auto ans = sol->levelOrder(tree->rootp_);
	cout << ans.size() << endl;	
	delete sol;
	delete tree;
	return 0;
}
