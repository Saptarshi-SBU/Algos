/*------------------------------------------------------------------------------
 *
 * Copyright(C) 2017 Saptarshi Sen
 *
 * Group Anagrams
 *
 *  +) Use Multimap O(n(klogk)(logH))
 *
 *  +) User HashMap with vector as value O(nklogk)
 *
 *  Multimap has a rb tree as value, which makes anagram grouping (insert) slow
 *
 *  HashMap indexes vector, which we append at tail hence faster
 *
 * https://leetcode.com/submissions/detail/134113322/
 * https://leetcode.com/submissions/detail/134116242/
 * ---------------------------------------------------------------------------*/
#include <set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {

    public:

    // Desc : Using MultiMap
    vector<vector<string>> groupAnagramsMultiMap(vector<string>& strs) {
        set<string> keys; // hold unique keys
        multimap<string, string> map; // hold anagrams
        vector<vector<string>> result;

        for (auto item : strs) {
            std::string key = item;
            sort(key.begin(), key.end());
            if (keys.find(key) == keys.end()) {
                keys.insert(key);
            }
            map.insert(std::pair<string, string>(key, item));
        }

        for (auto key : keys) {
            vector<string> ans;
            std::pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
                range = map.equal_range(key);
            for (auto iter = range.first; iter != range.second; iter++) {
                ans.push_back(iter->second);
            }
            result.push_back(ans);
        }

        return result;
    }

    // Desc : Using HashMap
    vector<vector<string>> groupAnagramsUnorderedMap(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> map;
        for (auto& item : strs) {
            string key = item;
            sort(key.begin(), key.end());
            map[key].push_back(item);
        }
        for (auto& items : map) {
            result.push_back(items.second);
        }
        return result;
    }

    // Main routine
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        return groupAnagramsUnorderedMap(strs);
    }
};

int
main(void) {
  Solution sol;
  vector<string> strings = { "ant", "tan" };
  sol.groupAnagrams(strings);
  return 0;
}
