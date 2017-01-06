/*-----------------------------------------------------------------------
 *
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Could you do it in O(n) time and O(1) space?
 *
 * Testing Done : Passed in Leetcode
 *
 * https://leetcode.com/submissions/detail/88129266/
 * --------------------------------------------------------------------*/

#include <iostream>
#include <list>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

ListNode* middle(ListNode *head) {

    if (!head)
       return nullptr;

    ListNode *p, *q;
    p = q = head;

    // A->B->C
    // A->B->C->D
    while (q && q->next != nullptr && q->next->next != nullptr) {
        p = p->next;
        q = q->next->next;
    }

    return p;
}

ListNode* reverse(ListNode* node, ListNode** head) {

    if (!node)
       return nullptr;

    if (node->next == nullptr) {
        *head = node;
        return node;
    }

    auto p = reverse(node->next, head);
    //set next node next to current
    p->next = node;
    //reset the node's next
    node->next = nullptr;
    return node;
}

bool isPalindrome(ListNode* head) {
   if ((!head) || (head->next == nullptr))
      return true;

   //Algorithm
   ListNode *mid, *split_head, *new_head;

   mid = middle(head);
   split_head = mid->next;
   mid->next = nullptr;
   reverse(split_head, &new_head);

   ListNode *p, *q;
   p = head;
   q = new_head;
   bool palindrome = true;

   while (p && q) {
      if (p->val != q->val) {
         palindrome = false;
         break;
      }
      p = p->next;
      q = q->next;
   }

   reverse(new_head, &split_head);

   p = head;
   while (p->next)
      p = p->next;

   p->next = split_head;

   return palindrome;
}

void print(ListNode *node) {
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

#define TESTCASE_0 0
#define TESTCASE_1 0
#define TESTCASE_2 0
#define TESTCASE_3 0
#define TESTCASE_4 1

int main(void) {

    ListNode *head = new ListNode(0);

    ListNode *p, *q;
    p = head;
#if TESTCASE_0
    p->next = new ListNode(1) ;
    p = p->next;
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(0);
    p = p->next;
#endif

#if TESTCASE_1
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(0);
    p = p->next;
    p->next = new ListNode(1);
    p = p->next;
#endif

#if TESTCASE_2
    p->next = new ListNode(1);
    p = p->next;
#endif

#if TESTCASE_3
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(0);
    p = p->next;
#endif

#if TESTCASE_4
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(0);
    p = p->next;
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(1);
    p = p->next;
#endif

    print(head);
#if 0
    ListNode *new_head;

    reverse(head, &new_head);
    print(new_head);

    reverse(new_head, &head);

    auto mid = middle(head);
    cout << mid->val << endl;
#endif
    cout << "IsPalindrome " << isPalindrome(head) << endl;;
}

