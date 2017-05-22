/*-----------------------------------------------------------------------------
 *
 * Copyright (C) 2017 Saptarshi Sen
 *
 * GridLand Metro : Merging Intervals O(nmlogn)
 *
 * The city of Gridland is represented as an  matrix where the rows are numbered
 * from  to  and the columns are numbered from  to .
 *
 * Gridland has a network of train tracks that always run in straight horizontal
 * lines along a row. In other words, the start and end points of a train track
 * are  and , where  represents the row number,  represents the starting column,
 * and  represents the ending column of the train track.
 *
 * The mayor of Gridland is surveying the city to determine the number of
 * locations where lampposts can be placed. A lamppost can be placed in any cell
 * that is not occupied by a train track.
 *
 * Given a map of Gridland and its  train tracks, find and print the number of
 * cells where the mayor can place lampposts.
 *
 * Note: A train track may (or may not) overlap other train tracks within the
 * same row.
 *
 * https://www.hackerrank.com/challenges/gridland-metro/submissions/code/44762446
 *
 * ---------------------------------------------------------------------------*/
#include <vector>
#include <map>
#include <fstream>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long unsigned int T;

class Solution {

    typedef std::vector<std::pair<T, T>> intervals;
    typedef std::map<T, intervals> intervalmap;

    protected:

        virtual intervals mergeRowInterval(intervals &i, bool print=false) {
            intervals v;
            sort(i.begin(), i.end(),
                    [] (const std::pair<T, T>& p, const std::pair<T, T>& q) {
                       return (p.first < q.first);
                    });

            T begin = 0, end = 0;
            for (auto& k : i) {
                // Fix : negative difference exceeds 1 for unsigned types
                if (!begin || (k.first <= end) || ((k.first - end) == 1)) {
                   if (!begin) begin = k.first;
                   end = std::max(k.second, end);
                } else {
                   v.push_back(make_pair(begin, end));
                   begin = k.first;
                   end = k.second;
                }
            }
            v.push_back(make_pair(begin, end));
            if (print) 
                for (auto &k : v)
                    cout << k.first << " : " << k.second << endl;
            return v;
        }

        virtual unsigned long int countUsedCells(const intervals &i) {
            unsigned long int count = 0;
            for (auto& k : i) {
               count+=(k.second - k.first + 1);
            }
            return count;
        }

        intervalmap  m_imap;
        T m_row;
        T m_col;

    public:

        void insert(T row, T col1, T col2) {
           m_imap[row].push_back(make_pair(col1, col2));
        }

        void merge(void) {
           intervalmap m;
           for (auto& i : m_imap) {
              m[i.first] = mergeRowInterval(i.second);
           }
           m_imap = m;
        }

        unsigned long int count(void) {
           unsigned long int count = 0;
           for (auto& i : m_imap) {
              count+=countUsedCells(i.second);
           }
           return (m_row*m_col) - count;
        }

        void printIntervals(void) const {
            for (auto &i : m_imap) {
               for (auto &k : i.second) {
                   cout << i.first << " " << k.first << ":" << k.second << endl;
               }
            }
        }

        explicit Solution(T row, T col) : m_row(row), m_col(col) {}
        virtual ~Solution() {}
};

void Test01(void) {
   Solution sol(4, 5);
   sol.insert(1, 1, 2);
   sol.insert(1, 4, 5);
   sol.insert(1, 1, 3);
   sol.insert(2, 1, 2);
   sol.insert(2, 4, 5);
   sol.insert(2, 1, 3);
   sol.merge();
   sol.printIntervals();
   cout << "Free Cells " << sol.count() << endl;
}

void Test02(void) {
   Solution sol(4, 4);
   sol.insert(2, 2, 3);
   sol.insert(3, 1, 4);
   sol.insert(4, 4, 4);
   sol.merge();
   sol.printIntervals();
   cout << "Free Cells " << sol.count() << endl;
}

void Test03(void) {
   T n,m,k;
   T r, ca, cb;
   ifstream ifile("test");
   ifile >> n >> m >> k;
   Solution sol(n, m);
   cout << n << " " << m << " " << k << endl;
   for (unsigned long int i = 0; i < k; i++) {
      ifile >> r >> ca >> cb;
      sol.insert(r, ca, cb);
   }
   sol.merge();
   sol.printIntervals();
   cout << sol.count() << endl;
}

int main() {
   Test01();
   Test02();
   Test03();
   return 0;
}
