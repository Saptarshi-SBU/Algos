/*
 * Remove K Digits
 *
 * +) DFS : O(n!)
 * +) Using Stack : O(N)
 *
 * https://medium.com/@saurav.agg19/remove-k-digits-8d5aa221751a
 *
 */
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string trimLeadingZeroes(string num) {
	int pos = 0;
	for (auto &c : num) {
           if (c == '0')
	       pos++;
	   else
	       return num.substr(pos, num.size() - pos);
	}
	return "0";
}

bool checkSmaller(string p, string q) {
	return std::stoul(p, nullptr, 10) < std::stoul(q, nullptr, 10);
}

//i->index to del
string removeKdigitsDFS(string num, int k, int i) {
	if (k <= 0)
	    return num.empty() ? "0" : trimLeadingZeroes(num);

	string result;
	for (size_t p = i; p < num.size(); p++) {
	    string ss = num.substr(0, p) + num.substr(p + 1, num.size());
	    std::cout << "=>" << ss << std::endl;
	    ss = trimLeadingZeroes(ss);
	    std::cout << "<=" << ss << std::endl;
	    string sr = removeKdigitsDFS(ss, k - 1, 0);
	    if (result.empty() || (sr.size() && checkSmaller(sr, result))) {
		result = sr;
	    	std::cout << "ans:" << ss << ":" << sr << std::endl;
	    }
	}
	return result;
}

// O(n)
string removeKdigitsStack(string num, int k) {
	string ans;
	std::stack<char> num_stack;

	num = trimLeadingZeroes(num);
	for (size_t i = 0; i < num.size(); i++) {
	    if (num_stack.empty())
	        num_stack.push(num.at(i));
	    else {
		while ((!num_stack.empty() && (num_stack.top() > num.at(i))) && k > 0) {
		    num_stack.pop();
		    k--;
	    	}
		if ((num_stack.empty() && num.at(i) == '0'))
			continue;
		num_stack.push(num.at(i));
	    }
	}

	// monotonic substring
	while (!num_stack.empty()) {
		//std::cout << num_stack.top() << std::endl;
		if (k > 0)
		    k--;
		else
		    ans.append(1, num_stack.top());
		num_stack.pop();
	}

	reverse(ans.begin(), ans.end());
	return ans.empty() ? "0" : ans;
}

//O(nCk) : factorial
string removeKdigits(string num, int k) {        
	if (num.empty() || num.size() < k)
	    return num;
	return removeKdigitsDFS(num, k, 0);
}

int main(void) {
	string str01 = "123456789";
	std::cout << str01 << ":" << removeKdigits(str01, 3) << std::endl;
	std::cout << str01 << ":" << removeKdigitsStack(str01, 3) << std::endl;

	string str02 = "4356";
	std::cout << str02 << ":" << removeKdigits(str02, 2) << std::endl;
	std::cout << str02 << ":" << removeKdigitsStack(str02, 2) << std::endl;

	string str03 = "10";
	std::cout << str03 << ":" << removeKdigits(str03, 2) << std::endl;
	std::cout << str03 << ":" << removeKdigitsStack(str03, 2) << std::endl;

	string str04 = "1432219";
	std::cout << str04 << ":" << removeKdigits(str04, 3) << std::endl;
	std::cout << str04 << ":" << removeKdigitsStack(str04, 3) << std::endl;

	string str05 = "10200";
	std::cout << str05 << ":" << removeKdigits(str05, 1) << std::endl;
	std::cout << str05 << ":" << removeKdigitsStack(str05, 1) << std::endl;

	string str06 = "1234567890";
	std::cout << str06 << ":" << removeKdigits(str06, 9) << std::endl;
	std::cout << str06 << ":" << removeKdigitsStack(str06, 9) << std::endl;

	string str07 = "10101010";
	std::cout << str07 << ":" << removeKdigits(str07, 3) << std::endl;
	std::cout << str07 << ":" << removeKdigitsStack(str07, 3) << std::endl;

	return 0;
}
