/*------------------------------------------------------------------------------------
 *
 * 	remove all adjacent duplicates
 *
 * ----------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

void remove_adj_duplicates(string& str) {

	stack<char> s;

	int p = str.length();
	while (p) {
		s.push(str.at(p - 1));
		p--;
	}

	string new_str;

	char c;
	char prev = '\0';

	while (!s.empty()) {

		c = s.top();
		s.pop();
		if (('\0' == prev) || (c != prev)) {
			new_str.append(1, c);
			prev = c;
		}
	}
	
	str = new_str;
}

void remove_adj_inplace(string& str) {

	int i = 0;
	int k = 0;
	int p = str.length();
	
	char prev = '\0';
	char curr;

	for (;i < p ;i++) {

		curr = str.at(i);
		if (('\0' == prev) || (curr != prev)) {
			prev = curr;
			continue;
		} else {
			str.replace(i, 1, 1, '#');
		}
	}

	//cout << str << endl;
	
	for (i = 0, k = 0; i < p ; i++) {
		curr = str.at(i);
		if (curr != '#') {
			str.replace(k, 1, 1, curr);
			k++;
		}
	}

	str.resize(k);
	//cout << str << endl;
}


int main(void) {

	string base = "aaaabbaccdde";
	string s1 = base;
	string s2 = base;

	remove_adj_duplicates(s1);
	cout << s1 << endl;
	remove_adj_inplace(s2);
	cout << s2 << endl;
	return 0;
}
