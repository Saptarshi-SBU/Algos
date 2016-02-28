/*-----------------------------------------------------------------------------
 *
 *
 * Implement Queue using stacks 
 *
 * ----------------------------------------------------------------------------*/

#include <iostream>
#include <stack>

using namespace std;

class Queue {

    stack<int> s1, s2;

public:

    // Push element x to the back of queue.

    void push(int x) {

        s1.push(x);
    }


    // Removes the element from in front of queue.

    void pop(void) {

        if (s2.empty()) {

            if (s1.empty())
                return;

            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }   
        }

        s2.pop();
    }



    // Get the front element.

    int peek(void) {

        if (s2.empty()) {

            if (s1.empty())
                return -1;

            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }

        }

        return s2.top();
    }



    // Return whether the queue is empty.

    bool empty(void) {

        if (s1.empty() && s2.empty())
            return true;
        else
            return false;
    }
};

int main(void) {
	Queue q;
	q.pop();
	q.push(3);
	cout << q.peek() << endl;
	return 0;
}
