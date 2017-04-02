/*------------------------------------------------------------------------
 * Copyright (C) : 2017, Saptarshi Sen
 *
 * Merge Intervals : O(nlogn)
 *
 * https://leetcode.com/submissions/detail/98792947/
 *
 * ----------------------------------------------------------------------*/

#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Definition for an interval.
 */

struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

class Solution {

public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;

        if (intervals.empty())
           return vector<Interval> ();

        // Fix:Memory Corruption on including <>equalto operator in lambda
        // Sort intervals based on start-time
        sort(intervals.begin(), intervals.end(),
           [] (const Interval& p, const Interval& q)
           { 
               if (p.start < q.start)
                  return true;
               else if (p.start > q.start)
                  return false;
               // if start times equal, sort based on end times
               // we do not see a re-sort based on end-times
               else
                  return p.end < q.end;
           });

#if DEBUG           
        for (auto&i : intervals)
           cout << i.start << ":" << i.end << endl;
#endif

        Interval newInterval(intervals.front());
        for (auto& i : intervals) {
            // Current Segment is a Candidate 
            if (newInterval.end < i.end) {
                // Fix : curr.end and next.start greater by 1 is not considered overlapped
                // Case : End of Old Segment
                if (newInterval.end < i.start) {
                   result.push_back(newInterval);
                   newInterval = i;
                } else {
                // Case : Old Segment Overlap with Current    
                   newInterval.end = i.end;
                }
            } // else Old Segment includes Current
        }
        result.push_back(newInterval);
        return result; 
    }
};

int main(void) {

   vector<Interval> v;
   v.push_back(Interval(1, 2));
   v.push_back(Interval(3, 6));

   Solution sol;
   vector<Interval> ans;
   ans = sol.merge(v);
   cout << "Merged Intervals " << endl;
   for (auto&i : ans)
       cout << i.start << ":" << i.end << endl;
   return 0;
}
