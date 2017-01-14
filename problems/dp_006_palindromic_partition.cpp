/*-----------------------------------------------------------------------
 *
 * Palindrome Partitioning Algorithm
 *
 * https://leetcode.com/submissions/detail/89232910/
 *
 * g++ -std=c++11 -DTEST_ALGORITHM dp_006_palindromic_partition.cpp
 *-----------------------------------------------------------------------*/
#include<string>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<unistd.h>
#include<cassert>

using namespace std;

void
print(vector<vector<string>> &map) {
   cout << "Total Count : " << map.size() << endl; 
   for (auto it = map.begin(); it != map.end(); it++) {
      for (auto j = (*it).begin(); j != (*it).end(); j++)
         cout << *j << " ";
      cout << endl;
   }   
}

bool
isPalindrome(string &s) {

    int p = 0;
    int q = s.length() - 1;

    while (p < q) 
        if (s.at(p++) != s.at(q--))
           return false;        
    return true;       
}    

//Algorithm : 
//Paradigm : Dynamic Programming
//Parition table contains for each splitting index, vectors of possible
//palindromic strings.
//We populate the partition table for string indexes from right to left
//As we traverse left by adding each character, we partition the new substring
//(formed with the new character added) into all possible substrings in search
//of possible new palindromes. Since we have pre-computed the paritioning results
// for earlier substrings, we re-use those results in our current computation
void
palindrome_partition(string &s, int p, unordered_map<int, vector<vector<string>>> &map) {

    vector<vector<string>> result;

    int len = s.length(); // str length
    int n = len - p; // substr length

    assert(p < len);
  
    if (map.find(p) != map.end())
       return; 

    // Partition String
    for (int i = 1; i <= n; i++)  {
       auto str = s.substr(p, i);
       // Process the partition 
       if (isPalindrome(str)) {
          // In case partition yields full string    
          if(str.length() == n) {
             vector<string> v;
             v.push_back(str);
             result.push_back(v);
             continue;
          }
          // Process other partition
          int next = p + i; 
          palindrome_partition(s, next, map);

          // Merge
          for (auto it = map[next].begin(); it != map[next].end(); it++) {
          // Fix : earlier performed insert on the iterator which was
          // modifiying the partition table of another index
             vector<string> v(*it);
             v.insert(v.begin(), str);  
             result.push_back(v);
          }
       }
    }
 
    // update the map with result for the current index
    if (!result.empty())
       map[p] = result;

    return;
}

int main(int argc, char **argv) {

     if (argc < 3) {
         cout << "Usage :  -s <string>" << endl;
         return -1;
     }    

     char c;
     string s;
     while ((c = getopt (argc, argv, "s:")) != -1) {
        switch (c) {
           case 's' :
               s = string(optarg);
               break;
           default:
               break;
        }       
    }

    if (s.empty())
       return -1;

#if TEST_PALINDROME
     cout << s << ":" << isPalindrome(s) << endl;
#endif     

#if TEST_ALGORITHM 

     vector<vector<string>> result;
     unordered_map<int, vector<vector<string>>> partition_map;

     // Try all possible string partitioning
     for (int i = s.length() - 1; i >= 0 ; i--)
        palindrome_partition(s, i, partition_map);

#if DEBUG    
    for (int i = 0; i < s.length(); i++) {
       cout << "DBG : " << i << " "; 
       print(partition_map[i]);
    }   
#endif

     vector<vector<string>>::iterator it;
     for (it = partition_map[0].begin(); it != partition_map[0].end(); it++)
        result.push_back(*it);    

     cout << "========Result==========" << endl;
     cout << "string length : " << s.length() << endl;
     print(result);

#endif    
    return 0;
}
