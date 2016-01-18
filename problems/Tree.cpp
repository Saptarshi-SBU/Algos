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
		
		int size(TreeNode *root) {
		    
		    if (!root)
		        return 0;
		        
		    return (1 + size(root->leftp_) + size(root->rightp_));
		}
		
		int identicalTrees(TreeNode *root1, TreeNode *root2) {
		    
		    if ((!root1) && (!root2))
		           return 0;
		   
		    if ((!root1) || (!root2) || (root1->data_ != root2->data_))
		           return -1;
		    
		    if (identicalTrees(root1->leftp_, root2->leftp_) == 0 && identicalTrees(root1->rightp_, root2->rightp_) == 0)
		        return 0;
		    else
		        return -1;
		 }
		 
		int max_height(TreeNode *root) {
		    
		    if (!root)
		         return 0;
		         
		    return 1 + max(max_height(root->leftp_), max_height(root->rightp_));
		} 
		
		void Mirror (TreeNode *rootp) {
		    
		  if (!rootp)
		        return;
		        
		  TreeNode *child = rootp->leftp_;
		  
		  rootp->leftp_ = rootp->rightp_;      
		  rootp->rightp_ = child;
		  
		  Mirror(rootp->leftp_);
		  Mirror(rootp->rightp_);
		  
		  return;
		}
		
		
		TreeNode *LCA(TreeNode *root, int key1, int key2) {
		    
		    if (!root)
		        return 0;
		    
		    if ((key1 < root->data_) && (key2 < root->data_))
		      return LCA(root->leftp_, key1, key2);
		    else if ((key1 > root->data_) && (key2 > root->data_))
		      return LCA(root->rightp_, key1, key2);
		    else 
		      return root;
		 }  
		 
		int LCAUtil(TreeNode *root, int key1, int key2, TreeNode **node) {
		  
		     int countmatch = 0;        
		     
		     if (!root)
		        return 0;
		        
		     countmatch = LCAUtil(root->leftp_, key1, key2, node) + LCAUtil(root->rightp_, key1, key2, node);
		     if ((key1 == root->data_) || (key2 == root->data_))
		         countmatch+=1;
		         
		     if (countmatch == 2) {
		         *node = root;
		         countmatch = 0;
		     }       
		     return countmatch;            
		} 
		 
		TreeNode *LCABT(TreeNode *root, int key1, int key2) {
		    
		    if (!root)
		        return 0;
		        
		    TreeNode *L = LCABT(root->leftp_, key1, key2);
		    
		    TreeNode *R = LCABT(root->rightp_, key1, key2);
		    
		    if (L && R)
		        return root;
		        
		    if ((key1 == root->data_) || (key2 ==  root->data_))
		        return root;
		        
		    return L ? L : R;
		}   
		
		int max_sum_ = 0;
		
		void maxsum(TreeNode *root, int *sum) {
		   
		      if (!root)
		        return;
		        
		     *sum+=root->data_;  
		      
		      maxsum(root->leftp_, sum);
		      maxsum(root->rightp_, sum);
		      
	          if ((*sum > max_sum_) && (!root->leftp_) && (!root->rightp_))
		          max_sum_ = *sum;
		          
		     *sum-=root->data_;
		      return;
		 }
	
		TreeNode* insert(TreeNode *node, int key) {
		    
		   if (!node)
		        return new TreeNode(key);
		        
		   if (key < node->data_)
		        node->leftp_ =  insert(node->leftp_, key);
		   else
		        node->rightp_ = insert(node->rightp_, key);
		        
		   return node;
		}  
		        
		TreeNode *PostOrder2BST(int array[], int start, int end) {
		    
		   int mid  = -1;
		   
		   if (start > end)
		        return 0;
	
	       TreeNode* node = new TreeNode(array[end]);
		    
	       for (int i = end - 1; i >= start; i--) {
	           if (array[i] > node->data_)
	                mid = i;
	       }
	
	        node->leftp_  = PostOrder2BST(array, start, mid -1);
		    node->rightp_ = PostOrder2BST(array, mid, end - 1);
		    
		    return node;
		}
		
		int max_path_sum_ = 0;
		
		int MaxSumPath(TreeNode *node) {
		    
		    if (!node)
		        return 0;
		        
		    int lsum = MaxSumPath(node->leftp_);
		    int rsum = MaxSumPath(node->rightp_);
		    
		    int p_sum  = max(max(node->data_ + lsum, node->data_ + rsum), node->data_);
		    int m_sum  = max(p_sum, node->data_ + lsum + rsum);
		    
		    int sum = max(p_sum, m_sum);
		    max_path_sum_ = max_path_sum_ < sum ? sum : max_path_sum_;
		          
		    return p_sum; 
		 }
		
		
		 void LevelOrderTraversal(void) {
		     
		     queue<TreeNode*> q;
		  
		  cout << "LevelOrderTraversal :";         
		     q.push(rootp_);  
		     while (!q.empty()) {
		         
		         TreeNode *node = q.front();
		         cout << node->data_ << "  ";
		         q.pop();
		         if (node->leftp_)
		             q.push(node->leftp_);
		         if (node->rightp_)
		             q.push(node->rightp_);
		     }     
		     cout << endl;
		 }
		 
		 int countLeaves(TreeNode *root) {
		     if (!root)
		        return 0;
		     else if (!(root->leftp_) && !(root->rightp_))  
		        return 1;
		     else
		        return countLeaves(root->leftp_) + countLeaves(root->rightp_);
		 }   
		 
		 void SpiralOrderTraversal(void) {
		     
		  queue<TreeNode*> q;
		  stack<TreeNode*> s;
		  
		  cout << "SpiralOrderTraversal :\n";    
		  
		     s.push(rootp_);  
		     while (!q.empty() || !s.empty()) {
		         
		         while (!s.empty()) {
		            TreeNode *node = s.top();
		            cout << node->data_ << "  ";
		            s.pop();
		            if (node->rightp_)
		                 q.push(node->rightp_);
		            if (node->leftp_)
		                 q.push(node->leftp_);
		         };
		         cout << endl;
		         while (!q.empty()) {
		            TreeNode *node = q.front();
		            cout << node->data_ << "  ";
		            q.pop();
		            if (node->rightp_)
		                 s.push(node->rightp_);
		            if (node->leftp_)
		                 s.push(node->leftp_);
		         };
		         cout << endl;
		     }; 
		     cout << endl;
		 }
		       
		 int SumCheck(TreeNode *node) {

		     if (!node || ((!node->leftp_) && (!node->rightp_)))  
		        return 1;
		     else {
		            int ldata = 0;
		            int rdata = 0;
		            
		            if (node->leftp_)
		                    ldata = node->leftp_->data_;
		            if (node->rightp_)
		                    rdata = node->rightp_->data_;
		                    
		            if ((node->data_ ==  ldata + rdata)
		                    && SumCheck(node->leftp_) && SumCheck(node->rightp_))
		                    return 1;
		            else
		                    return 0;
		     }
		 }
		 
		 int diameter_ = 0;
		 
		 int diameter(TreeNode *root) {
		     
		     if (!root)
		        return 0;
		        
		     int l = diameter(root->leftp_);
		     int r = diameter(root->rightp_);
		     int s = 1 + max(l, r);
		     
		     if (1 + l + r > diameter_)
		        diameter_ = 1 + l + r;
		           
		     return s;
		        
		  }
		  
		  void inorder_iterative(void) {
		      
		      bool done = false;
		      
		      stack<TreeNode*> s;
		            
		      TreeNode *node = rootp_;
		      
		      if (!node)
		        return;
		        
		      s.push(node);
		      
		      cout << "inorder_iterative :";
		      while (!done) {
		      
		          if (node->leftp_) {
		            node = node->leftp_;
		            s.push(node);
		          } else {
		            while (!s.empty()) {
		                    node = s.top();         
		                    cout << node->data_ << " ";
		                    s.pop();
		                    if (node->rightp_) {
		                        node = node->rightp_;
		                        s.push(node);
		                        break;
		                    }      
		            };
		            
		            if (s.empty())
		                done = true;
		          }
		      };
		      cout << endl;
		  }    

          int root_to_leaf_path(TreeNode *node, int sum) {
              
            if (!node)
                return 0;
                
            if ((!node->leftp_) && (!node->rightp_))
                return (sum - node->data_) ? 0 : 1;
            else
                return (root_to_leaf_path(node->leftp_,  sum - node->data_) || 
                       (root_to_leaf_path(node->rightp_, sum - node->data_)));
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
	cout << "Tree Size " << tree->size(tree->rootp_) << endl; 
	
	Tree *tree2 = new Tree(100);
	tree2->insert(25);
	tree2->insert(50);
	tree2->insert(200);
    tree2->insert(250);
	tree2->insert(150);
	tree2->insert(80);
	tree2->insert(75);

	cout << "Identical Trees : " << tree->identicalTrees(tree->rootp_, tree2->rootp_) << endl;
	cout << "Max height :" << tree->max_height(tree->rootp_) << endl;
	cout << "Max height :" << tree2->max_height(tree2->rootp_) << endl;
	
	tree->Mirror(tree->rootp_);
	tree->traverse(Tree::PREORDER_STACKLESS);
	TreeNode *res = tree->LCA(tree->rootp_, 200, 250);
	if (res)
	     cout << "LCA " << res->data_ << endl;
	
	TreeNode *node = 0;     
	tree2->LCAUtil(tree2->rootp_, 200, 250, &node);
	if (node)
	    cout << "LCA " << node->data_ << endl;
	
	cout << "LCA " << tree2->LCABT(tree2->rootp_, 200, 250)->data_ << endl;
	
	int sum = 0;
	tree->maxsum(tree->rootp_, &sum);
	cout << "Max Path Sum " << tree->max_sum_ << endl;

    Tree *tree3 = new Tree(100);
	tree3->insert(50);
    tree3->insert(200);
	tree3->insert(150);
	tree3->insert(250);
	tree3->insert(125);

    tree3->MaxSumPath(tree3->rootp_);
    
    cout << "Max Sum Path " << tree3->max_path_sum_ << endl;
	tree3->LevelOrderTraversal();
	tree3->SpiralOrderTraversal();
	
	tree3->diameter(tree3->rootp_);
	cout << "diameter :" << tree3->diameter_ << endl;
	tree3->inorder_iterative();
    delete tree;
	delete tree2;
	delete tree3;
}