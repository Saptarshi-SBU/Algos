/*
 *
 * Minimum number of Swaps to transform a string
 *
 * String has only two distinct characters
 *
 * The problem is based on reduction. My initial approach was to
 * scan the string from  left to right and attemot a swap. I was
 * running into the following issues :
 *
 *   a) reaching a state where pairs were reversible. I was handling
 *   the reversible case as a special case in the beginning
 *   b) my scan was based on similarity, even non-similar patterns
 *   can be swapped (2 twice) to trasnform (xy,yx->(xx,yy)->(yx,yx)
 *
 * My second approach was based on forming tuples and their reduction  
 * Complexity (O(N)), Space Complexity : O(1)
 */

#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int minimumSwapCount(string &s1, string &s2, int i, int j) {
        int count = 0;
        while (i < s1.size() && j < s2.size()) {
            if (s1.at(i) == s2.at(j)) {
                i++;
                j++;
                continue;
            }
            size_t k = 0;
            for (k = j + 1; k < s2.size(); k++) {
                if (s2.at(j) == s2.at(k) && s1.at(k) != s2.at(k)) {
                    swap(s1[i],s2[k]);
                    count++;
                    break;
                }
            }
            if (s1.at(i) != s2.at(j))
                break;
        }
        return s1.compare(s2) == 0 ? count : -1;
    }
    
int checkCharCountWise(string s1, string s2) {
        map<char,int> count_map;
        
        for (size_t i = 0; i < s1.size(); i++) {
            if (count_map.find(s1.at(i)) == count_map.end())
                count_map[s1.at(i)] = 0;
            count_map[s1.at(i)]++;
        }
        for (size_t i = 0; i < s2.size(); i++) {
            if (count_map.find(s2.at(i)) == count_map.end())
                count_map[s2.at(i)] = 0;
            count_map[s2.at(i)]++;
        }
        
        for (auto &cv : count_map) {
	    // cannot have odd count
            if (cv.second % 2)
                return -1;
        }
        
        return 0;
    }

int checkReverse(string s1, string s2) {
	int count = 0;
	string s2_rev = s2;
	reverse_copy(s2.begin(), s2.end(), s2_rev.begin());
	if (s1.compare(s2_rev) == 0) {
		for (size_t i = 0; i < s1.size(); i++) {
			if (s1.at(i) != s2.at(i))
				count++;
		}
	}
	return count;
}
   
// incorrect
int minimumSwapII(string s1, string s2) {
	int count;
        if (s1.compare(s2) == 0)
           return 0;

        if (checkCharCountWise(s1,s2) < 0) {
	   std::cout << "odd count" << std::endl;
           return -1;
	}

	if ((count = checkReverse(s1,s2)) != 0) {
	   std::cout << "swap count for reversible string :" << count << std::endl;
           return count;
	}

        return minimumSwapCount(s1, s2, 0, 0);
}

//correct
int checkPairs(string s1, string s2) {
	int count = 0, p_rem = 0, q_rem = 0;
	map<tuple<int, int>, int> pair_count;
	for (size_t i = 0; i < s1.size(); i++) {
		auto t = make_tuple(s1.at(i), s2.at(i));
		if (pair_count.find(t) == pair_count.end())
			pair_count[t] = 0;
		pair_count[t]++;
	}

	if (pair_count.find(make_tuple('x', 'y')) != pair_count.end()) {
		// reduce pair
		count = pair_count[make_tuple('x', 'y')] / 2;
		p_rem = pair_count[make_tuple('x', 'y')] % 2;
	}
	if (pair_count.find(make_tuple('y', 'x')) != pair_count.end()) {
		count += (pair_count[make_tuple('y', 'x')] / 2);
		q_rem = pair_count[make_tuple('y', 'x')] % 2;
	}

	if (p_rem == q_rem)
		count += (2 * p_rem);
	else if (((p_rem > 0) && !q_rem) || ((q_rem > 0) && !p_rem))
		count = -1;
	return count;
}
int minimumSwap(string s1, string s2) {
	return checkPairs(s1, s2);
}

void testCase001(void) {
	string s1 = "xx";
	string s2 = "yy";
	std::cout << "ans :" << minimumSwap(s1, s2) << " expected :" << 1 << std::endl;
}

void testCase002(void) {
	string s1 = "xxxxy";
	string s2 = "yxxxx";
	std::cout << "ans :" << minimumSwap(s1, s2) << " expected :" << 2 << std::endl;
}

void testCase003(void) {
	string s1 = "xx";
	string s2 = "xy";
	std::cout << "ans :" << minimumSwap(s1, s2) << " expected :" << -1 << std::endl;
}

int main(void) {
	testCase001();
	testCase002();
	testCase003();
	return 0;
}
