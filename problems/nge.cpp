#include <iostream>
#include <stack>

#define ARRAY_LEN 6

using namespace std;

int main(void) {
	int arr[ARRAY_LEN] = { 10, 20, 5, 7, 45, 10};
	int next_greater[ARRAY_LEN];

	int i,k;
	std::stack<int> st;

	for ( i = 0; i < ARRAY_LEN; i++) {
		next_greater[i] = -1;
	}	

	st.push(arr[0]);
	i = 1;
	while(i < ARRAY_LEN) {
		if (!st.empty() && (arr[i] > st.top())) {
			std::cout << " nge : " << st.top() << " : " << arr[i] << std::endl;
			st.pop();
			continue;
		} 
		st.push(arr[i++]);
	}

	while(!st.empty()) {
		std::cout << " nge : " << st.top() << " : " << -1 << std::endl;
		st.pop();
	}

	return 0;
}
	
	
	
