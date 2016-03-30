#include <functional>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class MedianFinder {

    /* max-heap */

    std::priority_queue <int, std::vector<int>, std::less<int>> p;

    /* min-heap */

    std::priority_queue <int, std::vector<int>, std::greater<int>> q;

    double median_;

    void balance(void) {

        if (p.empty() && q.empty())
            return;

        int psize = p.size();
        int qsize = q.size();

        int sum   = psize + qsize;
        int delta = psize - qsize;

        if (delta < -1) {
            p.push(q.top());
            q.pop();
        } else if (delta > 1) {
            q.push(p.top());
            p.pop();
        }  

        if (sum % 2)
            median_ = psize > qsize ? p.top() : q.top();
        else
            median_ = (double)(p.top() + q.top())/2.0;
    }

public:

    // Adds a number into the data structure.

    void addNum(int num) {

        if (p.empty() && q.empty()) {
            p.push(num);

        } else if (q.empty()) {
            int mp = p.top();
            if (num > mp) 
                q.push(num);
            else
                p.push(num);
        } else {       
            int mp = p.top();
            int mq = q.top();
            if (num >= mq)
                q.push(num);
            else
                p.push(num);
        }

        balance();
    }

    // Returns the median of current data stream

    double findMedian() {
        return median_;
    }

};



// Your MedianFinder object will be instantiated and called as such:

// MedianFinder mf;

// mf.addNum(1);

// mf.findMedian();

int main(void) {

 MedianFinder mf;
 mf.addNum(3);
 mf.addNum(4);
 mf.addNum(2);
 mf.addNum(100);
 mf.addNum(1);
 mf.addNum(1);
 cout << mf.findMedian() << endl;
 return 0;	

}


