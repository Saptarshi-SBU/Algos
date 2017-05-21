/*******************************************************************************************************
 *
 * Copyright (C) 2017, Saptarshi Sen
 *
 * Minimal number of radio-transmitters O(n)
 *
 * Hackerland is a one-dimensional city with  houses, where each house  is located at some  on the
 * x-axis. The Mayor wants to install radio transmitters on the roofs of the city's houses. Each
 * transmitter has a range, , meaning it can transmit a signal to all houses  units of distance away.
 * Given a map of Hackerland and the value of , can you find and print the minimum number of
 * transmitters needed to cover every house in the city? (Every house must be covered by at least one
 * transmitter) Each transmitter must be installed on top of an existing house.
 * Input Format
 * The first line contains two space-separated integers describing the respective values of
 * (the number of houses in Hackerland) and  (the range of each transmitter).
 * The second line contains  space-separated integers describing the respective locations of each
 * house (i.e., ).

 * Constraints : There may be more than one house at the same location.
 *
 * https://www.hackerrank.com/challenges/hackerland-radio-transmitters/submissions/code/44746714
 * *****************************************************************************************************/
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

//Using Iterators and lower_bound API
int CalculateMinimumTransmitters_Iterators(vector<int>& pos, int range) {
    int nr_transmitters = 0;

    if (pos.empty()) {
        return 0;
    }

    // house positions need to be ordered for scanning.
    // Besides, there can be duplicates
    sort (pos.begin(), pos.end());

    bool done = false;
    std::vector<int>::iterator boundary, center = pos.begin();
    while (!done) {
       // Expand till 1*range
       if (center != pos.end()) {
          boundary = std::lower_bound(center, pos.end(), *center + range);
          if (boundary != pos.end() && (*boundary > *center + range)) {
             center = --boundary;
          } else {
             center = boundary;
          }
       }

       // Extend till 2*range
       if (center != pos.end()) {
          boundary = std::lower_bound(center, pos.end(), *center + range);
          // Fix : lower bound returns only the first matching; so for
          // for duplicate items, iterator has to be incremented/advanced;
          while (boundary != pos.end() && (*boundary == *center + range))
             boundary++;
          center = boundary;
       }

       // End
       if (center == pos.end())
           done = true;

       nr_transmitters++;
    }
    return nr_transmitters;
}

//Without iterators
int CalculateMinimumTransmitters(vector<int>& pos, int range) {
    int nr_transmitters = 0;
    const int n = pos.size();
    sort (pos.begin(), pos.end());
    int i = 0, center = 0;
    while (i < n) {
       for (center = i; i < n && pos[i] <= pos[center] + range; i++);
       for (center = i - 1; i < n && pos[i] <= pos[center] + range; i++);
       nr_transmitters++;
    }
    return nr_transmitters;
}

void Test01(void) {
    int n = 7;
    int k = 2;
    vector<int> x= { 9, 5, 4, 2, 6, 15, 12};
    cout << CalculateMinimumTransmitters(x, k) << endl;
}

void Test02(void) {
    int n = 5;
    int k = 1;
    vector<int> x= { 1, 2, 3, 4, 5};
    cout << CalculateMinimumTransmitters(x, k) << endl;
}

void Test03(void) {
    int n = 8;
    int k = 2;
    vector<int> x= { 7, 2, 4, 6, 5, 9, 12, 11};
    cout << CalculateMinimumTransmitters(x, k) << endl;
}

void Test04(void) {
    int n,k;
    unsigned long int val;
    vector<int> x;
    ifstream ifile("test");
    ifile >> n >> k;
    while (ifile >> val)
        x.push_back(val);
    cout << CalculateMinimumTransmitters(x, k) << endl;
}

void Test05(void) {
    int n,k;
    unsigned long int val;
    vector<int> x;
    ifstream ifile("test2");
    ifile >> n >> k;
    while (ifile >> val)
        x.push_back(val);
    cout << CalculateMinimumTransmitters_Iterators(x, k) << endl;
}

int main(){
    Test01();
    Test02();
    Test03();
    Test04();
    Test05();
    return 0;
}

