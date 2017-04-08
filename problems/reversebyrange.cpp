/*-----------------------------------------------------------------------------
 *
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Reverse Link List II : reverse in a range, One-pass
 *
 * https://leetcode.com/submissions/detail/99455139/
 *
 * --------------------------------------------------------------------------*/
#include <cassert>
#include <iostream>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

class Solution {

public:

    // n should be positive
    // Case 1 : return NULL if n <= 0
    // Case 2 : return NULL if n > length of list
    ListNode* GetNthNode(ListNode* node, int m) {
        if (m > 0) {
           int count = 1;
           while (node && count++ < m) {
              node = node->next;
           }
          // problem has a constraint: m < Length
           assert (count >= m);
           return node;
        }

        return NULL;
    }

   // n : nr elements to reverse
   // q : node following nr elements
    ListNode* reverse(ListNode* node, int n, ListNode** q) {
        // we reached end of list or 
        // n > length of list, so that we never reach base case
        if ((node == NULL) || (node->next == NULL)) {
           return node;
        }   
       
        // if last element, capture next in the group
        // Note n is NOT 0-based
        if (n == 1) {
           *q = node->next;
            return node;
        }   

        auto rhead = reverse(node->next, --n, q);
        if (node->next) {
           node->next->next = node;
           node->next = NULL;
        }
        return rhead;
    }

    // m : position
    // n : range from m in the list
    ListNode* reverseBetween(ListNode* head, int m, int n) {

        if ((head == NULL) || (n <= 1)) {
           return head;
        }

        ListNode* rhead = NULL;
        ListNode* rtail = NULL;

        ListNode* nthnext = NULL;
        ListNode* mthprev = GetNthNode(head, m - 1);

        if (mthprev) {
           // case m after head
           rtail = mthprev->next;
           rhead = reverse(mthprev->next, n, &nthnext);
           mthprev->next = rhead;
           rtail->next = nthnext;
        } else {
           // case m itself at head
           rhead = reverse(head, n, &nthnext);
           head->next = nthnext;
        }    

        return mthprev ? head : rhead;
    }

    void Print(ListNode* head) {
       while (head) {
          cout << head->val << " ";
          head = head->next;
       }
       cout << endl;   
    }    
};

int main(void) {

   ListNode *head = new ListNode(1);  
   auto node = new ListNode(2);
   head->next = node;
   node->next = new ListNode(3);
   node = node->next; 
   node->next = new ListNode(4);

   Solution sol;
   sol.Print(head);
   //auto rhead = sol.reverseBetween(head, 0, 0); 
   //auto rhead = sol.reverseBetween(head, 1, 0); 
   //auto rhead = sol.reverseBetween(head, 1, 2); 
   //auto rhead = sol.reverseBetween(head, 1, 3); 
   //auto rhead = sol.reverseBetween(head, 1, 4); 
   auto rhead = sol.reverseBetween(head, 2, 4); 
   //auto rhead = sol.reverseBetween(head, 3, 2); 
   //auto rhead = sol.reverseBetween(head, 20, 20); 
   sol.Print(rhead);
   return 0;
}
