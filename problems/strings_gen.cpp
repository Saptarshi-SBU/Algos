/*---------------------------------------------------------------------
 *
 * strings : unique characters, reverse, substring, rotate, anagrams
 *
 * g++ -std=c++11 strings_gen.cpp
 *
 *--------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool unique_characters(string s) {

	unordered_map<char, char> map;
	for (auto i : s) {
		if (map.find(i) == map.end())
			map[i] = i;
		else
			return false;
	}
	return true;
}

bool unique_characters2(string s) {

	char p ='\0';

	sort(s.begin(), s.end());
	for (auto i : s) {
		if (i == p)
			return false;
		else
			p = i;
	}	
	return true;
}

void reverse(string& s) {
	int p = 0;
	int q = s.length() - 1;

	while (p < q) {
		s.at(p) = s.at(p) ^ s.at(q);
		s.at(q) = s.at(p) ^ s.at(q); 
		s.at(p) = s.at(p) ^ s.at(q);
		p++;
		q--;
	}
}

void reverse_r(string& s, int p, int q) {

	if (p >= q)
		return;

	s.at(p) = s.at(p) ^ s.at(q);
	s.at(q) = s.at(p) ^ s.at(q); 
	s.at(p) = s.at(p) ^ s.at(q);
	reverse_r(s, ++p, --q);
}

int remove_duplicates(string& s) {
	int k = 0;
	unordered_map<char, char> map;
	
	for (auto i : s)
		map[i] = i;
	for (auto i : map)
		s.at(k++) = i.first;
	s.resize(k);
}

bool anagrams(string s1, string s2) {

	int k = 0;

	if (s1.length() != s2.length())
		return false;
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	return (s1 == s2) ? true : false;
}

string rotate(string s, int count) {
	
	reverse_r(s, 0, s.length() - 1);
	reverse_r(s, 0, count - 1);
	reverse_r(s, count, s.length() - 1);
	return s;
}

bool string_rotated(string s1, string s2) {

	if (s1.length() != s2.length())
		return false;

	int count = 0;

	char p = s1.at(0);

	for (auto i : s2) {
		if (p == i)
			break;
		else
			count++;
	}

	if (s1 == rotate(s2, s2.length() - count))
		return true;
	else
		return false;
}


void build_suffix_array(vector<string>& v, string s) {

	int k = 0;
	int n = s.length();
	for (auto i : s) {
		v.push_back(s.substr(k, n - k));
		k++;
	}

	sort(v.begin(), v.end(), [] (string s1, string s2) { return s1.compare(s2) < 0 ? true : false; } );
	#if DEBUG	
	for (auto i : v) 
		cout << i << endl;
	#endif
}


bool check_substring(string s, string sub) {

	vector<string> v;
	build_suffix_array(v, s);

	int p = 0;
	int q = s.length() - 1;
	int n =  sub.length();

	while (p <= q) {

		int m = (p + q)/2;
		string sub_main = v.at(m).substr(0, n);
		int ret = sub.compare(sub_main);
		cout << m << "  " << sub_main << "  " << sub << "  " << ret << "  " << p << "  " << q << endl;

		if (!ret)
			return true;
		else if (ret > 0) //sub > sub_main
			p = m + 1;
		else if (ret < 0) // sub < sub_main
			q = m - 1;
	}	
	return false;
}
 
int main(void) {
	string s = "abcaaa";
	cout << unique_characters(s) << endl;
	cout << unique_characters2(s) << endl;
	reverse(s);
	cout << s << endl;
	reverse_r(s, 0, s.length() - 1);
	cout << s << endl;
	remove_duplicates(s);
	cout << s << endl;
	string s1 = "bbbbbb";
	string s2 = "aaaaaa";
	cout << anagrams(s1, s2) << endl;
	string s3 = "abbbbbb";
	string s4 = "cbbbabb";
	cout << string_rotated(s3, s4) << endl;
	cout << s4 << endl;
	string s5 = "bcabbcabbbab";
	string s6 = "bab";
	cout << check_substring(s5, s6) << endl;
	return 0;
}
