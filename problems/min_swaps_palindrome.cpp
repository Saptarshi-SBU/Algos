/*
 * Write a program to count minimum number of swaps needed to
 * convert a string to a palindrome
 */

// abcdbca -> 0 swaps
// abcdabc -> 1 swap
// aaabccc -> NA
// aaabbabb
//
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int count_min_swaps(string value_str) {
	int count_swaps = 0;
	unordered_map<char, vector<int>> string_map;

	// fill the map
	for (int i = 0; i < value_str.size(); i++) {
		char key = value_str[i];
		if (string_map.find(key) == string_map.end())
			string_map[key] = vector<int>();
		string_map[key].push_back(i);
	}

#ifdef DEBUG
	for (int i = 0; i < value_str.size(); i++) {
		char key = value_str[i];
		std::cout << key << ":" << string_map[key].size() << std::endl;
	}
#endif
	int odd_count = 0, odd_pos = -1;
	int nlen = value_str.size();

	if (nlen == 0)
		return 0;

	if (nlen == 1)
		return 1;

	for (auto& i : string_map) {
		if (i.second.size() % 2) {
#ifdef DEBUG
			std::cout << i.first << std::endl;
#endif
			odd_count++;
			odd_pos = i.second[0];
		}
	}

	if (nlen % 2 && odd_count != 1) {
		std::cerr << "cannot form a palindrome with the given string"
		          << std::endl;
		return -1;
	}

	if (nlen % 2 == 0 && odd_count != 0) {
		std::cerr << "cannot form a palindrome with the given string "
		          << "odd count:" << odd_count
		          << std::endl;
		return -1;
	}

	int p, q, mid = nlen / 2;

	if (nlen % 2) {
		p = mid - 1;
		q = mid + 1;
		if (value_str[mid] != value_str[odd_pos]) {
			auto it = string_map.find(value_str[mid]);
			auto mid_it = std::find(it->second.begin(), it->second.end(), mid);
			it->second.erase(mid_it);
			it->second.push_back(odd_pos);

			it = string_map.find(value_str[odd_pos]);
			auto odd_it = std::find(it->second.begin(), it->second.end(), odd_pos);
			it->second.erase(odd_it);
			it->second.push_back(mid);

			std::swap(value_str[mid], value_str[odd_pos]);
			count_swaps++;
		}
	} else {
		p = mid - 1;
		q = mid;
	}

	while (p >= 0 && q < nlen) {
//#ifdef DEBUG
		std::cout << " p:" << p << " q:" << q
		          << " str:" << value_str << std::endl;
//#endif
		if (value_str[p] == value_str[q]) {
			p--; q++;
			continue;
		}

		auto it = string_map.find(value_str[p]);
		assert (it != string_map.end());
		int pos = -1;
		for (auto pos_it = it->second.begin(); pos_it != it->second.end(); pos_it++) {
			pos = *pos_it;
			if (pos != p)
				break;
		}
		assert (pos != p);

		auto p_it = std::find(it->second.begin(), it->second.end(), p);
		it->second.erase(p_it);

		auto pos_it = std::find(it->second.begin(), it->second.end(), pos);
		it->second.erase(pos_it);
		if (!it->second.size())
			string_map.erase(it->first);
		
		it = string_map.find(value_str[q]);
		assert (it != string_map.end());
		auto q_it = std::find(it->second.begin(), it->second.end(), q) ;
		it->second.erase(q_it);
		it->second.push_back(pos);

		std::swap(value_str[q], value_str[pos]);
		count_swaps++;
		p--; q++;
	}
	return count_swaps;
}

int main(void) {
	int result;

	string value_str_01 = "abcdabc"; result = count_min_swaps(value_str_01);
	std::cout << value_str_01 << ":" << result << std::endl;

	string value_str_02 = "abcddabc"; result = count_min_swaps(value_str_02);
	std::cout << value_str_02 << ":" << result << std::endl;

	string value_str_03 = "aba"; result = count_min_swaps(value_str_03);
	std::cout << value_str_03 << ":" << result << std::endl;

	string value_str_04 = "ababdabab"; result = count_min_swaps(value_str_04);
	std::cout << value_str_04 << ":" << result << std::endl;

	string value_str_05 = "dabababab"; result = count_min_swaps(value_str_05);
	std::cout << value_str_05 << ":" << result << std::endl;

	string value_str_06 = "daaaabbbb"; result = count_min_swaps(value_str_06);
	std::cout << value_str_06 << ":" << result << std::endl;

	string value_str_07 = "aabcb"; result = count_min_swaps(value_str_07);
	std::cout << value_str_07 << ":" << result << std::endl;

	return 0;
}
