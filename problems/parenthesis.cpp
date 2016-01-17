/*--------------------------------------------------------------------------------------
 *
 *
 * parenthesis Match
 * g++ -g -o balance parenthesis_match.cpp 
 * ./balance "(())"
 * -------------------------------------------------------------------------------------*/

#include <iostream>
#include <queue>
#include <stack>

#define SIZE(x) (sizeof(x)/sizeof(x[0]))

using namespace std;

char open[] = { '(', '{', '['};

char close[] = { ')', '}', ']'};

int isMatch(char p, char q) {

	if ((p == '(' && q == ')') || (p == '{' && q == '}') || (p == '[' && q == ']'))
		return 1;
	else
		return 0;
}

int isOpen(char c) {
	for(int i = 0; i < SIZE(open); i++)
		if (open[i] == c)
			return 1;
	return 0;
}

int isClose(char c) {
	for(int i = 0; i < SIZE(open); i++)
		if (close[i] == c)
			return 1;
	return 0;
}

int parenthesis_match(queue<char> q) {

	stack<char> s;

	while (!q.empty()) {

		char p = q.front();
		
		if (isOpen(p)) {
			q.pop();
			s.push(p);
			
		} else if (isClose(p)) {

			if (s.empty())
				return -1;
			else {
				do {
					char m = s.top();
					if (isOpen(m)) {
						if (!isMatch(m, p)) {
							return -1;
						} else {
							s.pop();
							q.pop();
							break;
						}
					} else {
						s.pop();
					}
				} while (s.size());
			}
		} else {
			s.push(p);
			q.pop();
		}
	};
	
	if (s.empty())
		return 0;
	else
		return -1;
}
			
int main(int argc, char **argv) {

	queue<char> q;

	if (argc != 2)
		return -1;

	char *p = argv[1];
	while (*p != '\0') {
		q.push(*p);
		p++;
	};

	cout << "Balanced : " << parenthesis_match(q) << endl;
}
