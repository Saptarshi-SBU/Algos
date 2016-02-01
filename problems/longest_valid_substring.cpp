/*-------------------------------------------------------------------
 *
 *  longest valid substring with parenthesis
 *
 * -----------------------------------------------------------------*/
#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

using namespace std;

#define OPENP  '('
#define CLOSEP ')'

class Parenthesis_Solver {

		
		string str_;
		stack<char> s_;
		int max_pair_;

	public :
		Parenthesis_Solver(string str): str_(str) {}

	       ~Parenthesis_Solver() {}

		int get_longest_valid(void) {
			return max_pair_*2;

		}

		void process(void) throw () {
			int i = 0;
			int count = 0;
			int p = str_.length();

			if (!p) 
				throw logic_error("null string");

			for (i = 0; i < p; i++) {

				if ((str_.at(i) == CLOSEP) && s_.empty()) {
					continue;
				} else if (str_.at(i) == OPENP) {
					s_.push(str_.at(i));
				} else if (str_.at(i) == CLOSEP) {
					s_.pop();
					count++;
					if (count > max_pair_)
						max_pair_ = count;
	//				if (s_.empty())
	//					count = 0;
				}			
			}
		}
};

int main(void) {
//	string s = "(())";
//	string s = "(()";
//	string s = ")()())";
	string s = "()(()))))";
	Parenthesis_Solver *p = new Parenthesis_Solver(s);
	p->process();
	cout << "Get Longest substring " << p->get_longest_valid() << endl;
	return 0;
}  

		

	

