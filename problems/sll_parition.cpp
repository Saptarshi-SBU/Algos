/*----------------------------------------------------------
 *
 * SLL Partition.  Both copy and in-place version.
 *
 * Complexity O(n)
 *
 * ---------------------------------------------------------*/

#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

typedef struct node_t {
    int val;
    struct node_t* next;

    node_t(int value):val(value), next(NULL) {}

}node_t;

struct SLL {
    node_t *head;
    node_t *tail;

    SLL():head(NULL), tail(NULL) {}
    ~SLL() {
        while (head) {
            auto curr = head;
            head = head->next;
            delete curr;
        }

        head = NULL;
    }

    void push_back(int val) {

        try {
           node_t *node = new node_t(val);
           if (tail) {
              tail->next = node;
              tail = node;
           } else {
              head = tail = node;
           }
        } catch (exception e) {
           throw "Out of Memory";
        }
    }

    void push_front(int val) {

        try {
           node_t *node = new node_t(val);
           if (head) {
               node->next = head;
               head = node;
           } else {
              head = tail = node;
           }
        } catch (exception e) {
           throw "Out of Memory";
        }
    }

    void print(void) const {
        auto curr = head;
        while (curr) {
            cout << curr->val << "->";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    SLL* partition(const int n) {

        if (!head)
            return NULL;

        SLL *parted_sll = new SLL();

        int val = -1;

        auto curr = head;

        while (curr) {
            val = curr->val;
            if (val <= n)
               parted_sll->push_front(val);
            else
               parted_sll->push_back(val);
            curr = curr->next;
        }

        return parted_sll;
    }

    // in-place version
    void partition2(const int n) {

        node_t* front = NULL;
        node_t* rear = NULL;

        if(!head)
            return;

        auto temp = head;

        while(temp){

           node_t* temp_next = temp->next;

           if(!front || !rear){
              front = rear = temp;
              temp->next = NULL;
           } else if(temp->val <= n){
              temp->next = front;
              front = temp;
           }else{
              rear->next = temp;
              temp->next = NULL;
              rear = temp;
           }
           temp = temp_next;
        }

        head = front;
        tail = rear;
    }
};

void populate(SLL *sll) {

    for (int i = 0; i < 10; i++)
       sll->push_back(i);

    for (int i = 0; i < 10; i++)
       sll->push_front(i);
}

int main(void) {

    SLL *sll = new SLL();
    populate(sll);
    sll->print();
    auto psll = sll->partition(5);
    if (psll)
        psll->print();
    sll->partition2(5);
    sll->print();
    return 0;
}

