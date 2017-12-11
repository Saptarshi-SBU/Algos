/*
 * Copyright (C) 2017 Saptarshi Sen
 *
 * Substring with concatenation of all words
 *
 * Complexity :
 *    +) Linear : Sliding Window with maps as frequency counter
 *       Spatial complexity  O(mk)
 *       https://leetcode.com/submissions/detail/131552415/
 *
 *    +) Linear : Indexes per item and then dfs like search
 *       to look up candidate indexes.
 *       Spatial Complexity can be  O(mn)
 * Notes:
 *    C++ member function with return type and if no return is
 *    passed. The result is UNDEFINED. Leads to Segault or
 *    double free issues.
 *
 *    multimap use equal_range
 * g++ -std=c++11 concatsubstring_search.cpp -g -DDEBUG -Wall
 */

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <iostream>
#include <cassert>

using namespace std;

#define CPPUNIT_ASSERT(condition) assert((condition))
#define CPPUNIT_ASSERT_EQUAL(expected, actual) assert((expected) == (actual))
#define CPPUNIT_ASSERT_MESSAGE(message, condition) \
   do { \
      std::cout << message << std::endl; \
      assert(condition); \
   } while (0);

class Solution {
public:
      int baselen;
      unordered_map<std::string, int> mainDict;

      std::vector<int> findSubstring(std::string s, std::vector<string>& words)
      {
         std::vector<int> result;

         if (words.empty() || (s.length() == 0)) {
            return result;
         }

         baselen = words[0].length();

         // frequency counter
         for (auto &i : words) {
            if (mainDict.find(i) == mainDict.end()) {
               mainDict.insert(std::make_pair(i, int(1)));
            } else {
               mainDict.at(i) += 1;
            }
         }

         // note: scan covers all possible arrangements
         for (int shift = 0; shift < baselen; shift++) {
            int count = 0;
            int index = shift;
            unordered_map<std::string, int> curDict; // local dictionary

            for (int i = shift; i <= static_cast<int>(s.length()) - baselen; i+=baselen) {
                std::string curWord(s.substr(i, baselen));
                if (mainDict.find(curWord) == mainDict.end()) {
                   count = 0;
                   curDict.clear();
                   index = i + baselen;
                } else {
                   // Word present
                   if (curDict.find(curWord) == curDict.end()) {
                      curDict.insert(std::make_pair(curWord, int(1)));
                   } else {
                      curDict.at(curWord) += 1;
                   }

                   count++;
                   while (curDict.at(curWord) > mainDict.at(curWord)) {
                      std::string temp(s.substr(index, baselen));
                      curDict.at(temp) -= 1;
                      count--;
                      index = index + baselen;
                   }

                   if (count == static_cast<int>(words.size())) {
                      std::string temp(s.substr(index, baselen));
                      curDict.at(temp) -= 1;
                      result.push_back(index);
                      index = index + baselen;
                      count--;
                   }
                }
            }
         }
         return result;
      }
};

class OldSolution {
	public:
		// k
		int baselen;
		// word index tree
		unordered_multimap<string, set<int>> kv;

		OldSolution() {}

		~OldSolution()
		{
			kv.clear();
		}

		std::vector<int> findSubstring(std::string s, std::vector<string>& words)
		{
			int next_pos = 0, lowest;
			vector<int> result;
			vector<int> scan_indices;

			if (words.empty()) {
				return std::vector<int>();
			}

			init_indextree(s, words);

#           ifdef DEBUG
            print_wordindex();
#           endif

			do {
#               ifdef DEBUG
                std::cout << "NEXT pos :" << next_pos << std::endl;
#               endif
                if ((s.length() - next_pos) < (baselen * words.size())) {
                   break;
                }
		  	    scan_indices.clear();
				// pick index next to or equal 'next'
				for (auto &entry : kv) {
					set<int>::iterator iter =
						std::lower_bound(entry.second.begin(), entry.second.end(), next_pos);
					if (iter != entry.second.end()) {
						scan_indices.push_back(*iter);
					}
				}
                if (scan_indices.empty()) {
                   break;
                }
#               ifdef DEBUG
				std::sort(scan_indices.begin(), scan_indices.end());
                std::cout << "scanned indices :";
                for (auto &i : scan_indices) {
                   std::cout << i << " ";
                }
                std::cout << std::endl;
#               endif
				lowest = *std::min_element(scan_indices.begin(), scan_indices.end());
				if (match_indices(lowest, words)) {
				   result.push_back(lowest);
#                  ifdef DEBUG
                   std::cout << "Match" << std::endl;
#                  endif
				}
				next_pos = lowest + 1;
			} while (true);

            return result;
		}

		void init_indextree(std::string s, std::vector<std::string> &wordvec)
		{
#           ifdef DEBUG
            std::cout << "main string " << s << std::endl;
#           endif

			baselen = wordvec[0].length();

			// initialize index tree
			for (auto &word : wordvec) {
               kv.insert(std::make_pair(word, set<int>()));
			}

			// create indexes
			for (size_t pos = 0; pos + baselen <= s.length(); pos++) {
				std::string sub(s.substr(pos, baselen));
                auto range = kv.equal_range(sub);
                for (auto iter = range.first; iter != range.second; ++iter) {
					iter->second.insert(pos);
                }
			}
		}

		bool match_indices(int lowest, std::vector<std::string>& wordvec)
		{
            int window;
            std::set<int> match;

            window = baselen * wordvec.size();
			for (auto &entry : kv) {
               for (int i = lowest; i < (lowest + window); i += baselen) {
			      if (entry.second.find(i) != entry.second.end() &&
                     match.find(i) == match.end()) {
                     match.insert(i);
                     break;
                  }
               }
            }
			return match.size() == wordvec.size() ? true : false;
        }

		void print_wordindex(void)
		{
			std::cout << "printing index " << std::endl;
			for (auto &entry : kv) {
				cout << "word : " << entry.first << std::endl;
				for (auto &index : entry.second)
					cout << index << " ";
                cout << endl;
			}
		}
};

void TestA(void)
{
    Solution sol;
    vector<int> result;

	string mainA = "rajarimpirimprajarimpi";
	vector<string> wordsA = { "raja", "rimp" };
    result = sol.findSubstring(mainA, wordsA);
    CPPUNIT_ASSERT_MESSAGE("TestA running", (result.size() == 3));
}

void TestB(void)
{
    Solution sol;
    vector<int> result;

	string mainB = "oocatdogacat";
	vector<string> wordsB = { "cat", "dog" };
    result = sol.findSubstring(mainB, wordsB);
    CPPUNIT_ASSERT_MESSAGE("TestB running", (result.size() == 1));
}

void TestC(void)
{
    Solution sol;
    vector<int> result;

	string mainC = "oocatdogacat";
	vector<string> wordsC = { "cat", "dg" };
    result = sol.findSubstring(mainC, wordsC);
    CPPUNIT_ASSERT_MESSAGE("TestC running", (result.size() == 0));
}

void TestD(void)
{
   Solution sol;
   vector<int> result;

   string mainD = "wordgoodgoodgoodbestword";
   vector<string> wordsD = {"word", "good", "best", "good"};
   result = sol.findSubstring(mainD, wordsD);
   CPPUNIT_ASSERT_MESSAGE("TestD running", (result.size() == 1));
   CPPUNIT_ASSERT_EQUAL(result[0], 8);
}

int main(void) {
    TestA();
    TestB();
    TestC();
    TestD();
	return 0;
}
