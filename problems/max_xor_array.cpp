/*
 * Max XOR pair in an array
 * O(nlogk), k = 64, constant
 */
#include<algorithm>
#include<cassert>
#include<limits>
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

#define BYTES(x) (4*x)

class TrieNode {

      public :

      char bset;
      TrieNode *b0, *b1;

      TrieNode(unsigned int set) {
         bset = set ? '1' : '0';
         b0 = b1 = NULL;
      }

      TrieNode* nextb1(void) {
         return b1;        
      }

      TrieNode* nextb0(void) {
         return b0;        
      }
};

class Trie {

      TrieNode *rootp;

      public:

      Trie() {
	rootp = NULL;
      }

      ~Trie() {
        __clear(rootp);
      }
      
      void __clear(TrieNode *node) {
         if (!(node->b0) && !(node->b1))
             return;

         if (node->b0)
              __clear(node->b0);
         if (node->b1)
              __clear(node->b1);
         delete node;
      }

      void __insert(unsigned int bval, int pos, TrieNode *curr) {

         if (pos < 0)
             return;

         auto set = (1 << pos) & bval;

         if (!rootp) {
            rootp = new TrieNode(set);
             __insert(bval, pos, rootp);
            return;
         }

         if (set) {
  
	    if (!(curr->b1)) {
                auto node = new TrieNode(set);
                curr->b1 = node;
            }
            //cout << curr->b1->bset;  
            __insert(bval, --pos, curr->b1);

          } else {

            if (!(curr->b0)) {
                auto node = new TrieNode(set);
                curr->b0 = node;
            }
            //cout << curr->b0->bset;  
            __insert(bval, --pos, curr->b0);
          }

      }

      void insert(unsigned int bval) {
         __insert(bval, BYTES(sizeof(unsigned int)) - 1, rootp);
      }

      void __xor(unsigned int bval, int pos, unsigned int& result, TrieNode *curr) {

         if (pos < 0)
            return;

         assert(curr);

         auto set = (1 << pos) & bval;
    
         if (set) {
            if (curr->b0) {
                result|=(1 << pos);
                __xor(bval, --pos, result, curr->b0);
            } else { 
                __xor(bval, --pos, result, curr->b1);
            }
        } else {
            if (curr->b1) {
                result|=(1 << pos);
                __xor(bval, --pos, result, curr->b1);
            } else { 
                __xor(bval, --pos, result, curr->b0);
            }
        }
      }

      unsigned int compute_xor(unsigned int bval) {
	unsigned int result = 0;

        assert(rootp);

        __xor(bval, BYTES(sizeof(unsigned int)) - 1, result, rootp);
        return result;
      }

      void _traversal(TrieNode *curr) {
          if (!curr)
              return;
          _traversal(curr->b0);
          cout << curr->bset;
          _traversal(curr->b1);
      }

      void traversal(void) {
          _traversal(rootp);
      }
            
};

void algo(vector<unsigned long int>&v) {
   unsigned int max = 0;

   Trie* trie = new Trie();

   for (auto&i : v)
      trie->insert(i);

   for (auto&i : v) {
     auto ans = trie->compute_xor(i);
     max = ans > max ? ans : max;
   }

   cout << "max : " << max << endl; 
   delete trie;
}

int main(int argc, char **argv) {

   if (argc < 2) {
       cout << " Usage : exe <list of integers> " << endl;
       return -1;
   }
   
   vector<unsigned long int> v; 
   for (int i = 1; i < argc; i++)
       v.push_back(atoi(argv[i]));

   algo(v);  

   return 0;
}
