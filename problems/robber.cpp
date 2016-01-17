/*------------------------------------------------------------------------------
 *
 * robber.cpp
 *
 * g++ -g -DDEBUG -std=c++11 -o robber robber.cpp
 *
 * ----------------------------------------------------------------------------*/
#include<iostream>
#include<vector>
#include<stack>

using namespace std;

stack<int> s;

int max_amount(int i, vector<int>& v, vector<int>& max_sum) {

	if (i > v.size() - 1)
		return 0;

	if (i == v.size() - 1)
		return v.at(i);

	if (max_sum.at(i)) 
		return max_sum.at(i);

	int max = 0;

	for (auto k = (int)v.size() - 1; k >= i; k--) {
		auto curr = v.at(k) + max_amount(k + 2, v, max_sum);
		if (max < curr) {
			max = curr;
			s.push(k);
		}
		max_sum.at(k) = max;
	}
	return max_sum.at(i);
}

int main(void) {

	vector<int> v = {700, 500, 200, 500, 100, 500, 600, 800};

	vector<int> max_sum(v.size());
	max_sum.assign(max_sum.size(), 0);

	max_amount(0, v, max_sum);

#if DEBUG
	for (auto k : max_sum)
		cout << k << endl;
#endif

	cout << "Max Steal Money " <<max_sum.at(0) << endl;

	int n, next;

	n = next = -1;
	cout << "Path : ";
	while (!s.empty()) {
		n = s.top();
		if ((next == -1) || (next + 2 <= n)) {
			cout << n << " ";
			next = n;
		}
		s.pop();
	};
	cout << endl;

	return 0;
}
