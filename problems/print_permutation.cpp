/*----------------------------------------------------------------------
 *
 * Print Permutation
 * [n] : next number
 * [k] : loop
 * [s] : string : dfs
 * --------------------------------------------------------------------*/
#include <iostream>
#include <string>

using namespace std;

void 
permutation(int n, int k, string s) {
	if (k == 0) {
		cout << s << endl;
		return;
	}

	for (int i = 0; i < 10; i++) {
		string str = s;
		permutation((i + 1) % 10, k - 1, str.append(to_string(i)));
	}

	return;
}

int main(int argc, char **argv) {

	if (argc < 2)
		return -1;
	permutation(0, atoi(argv[1]), string("")); 
	return 0;
}
