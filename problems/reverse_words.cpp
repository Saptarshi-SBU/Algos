/*-------------------------------------------------
 *
 * reverse words in a string (Leetcode Problem)
 *
 * date : Feb 27 , 2016 (O(n))
 *
 * 	Solution 
	O(n) : O(1)
	1.0388e-05
	8.13e-06
	8.194e-06
	8.457e-06
	8.487e-06
	8.93e-06
	8.269e-06
	7.986e-06

	Solution 1
	O(n) : O(n) 
	1.499e-05
	1.5281e-05
	1.5126e-05
	2.248e-05
	1.5327e-05
	1.4885e-05
	1.59e-05
	1.5897e-05
 * -----------------------------------------------*/

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }
private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

class Solution1 {
public:
    void reverseWords(string &s) {
	string result = "";
	string word   = "";
	bool bFlag    = false;

	if (s.empty())
		return;
	
	for (auto i : s) {
		if ((' ' == i) && bFlag) {
			result = result.size() ? word + " " + result : word;
			bFlag  = false;
			word   = "";
                } else if (' ' == i) {
			continue;
		} else if (bFlag) {
			word.append(1, i);	
		} else {
			word.append(1, i);	
			bFlag = true;
		}
	}

	if (result.empty())
		s = word;
	else if (word.empty())
		s = result;
	else
		s = word + " " +  result;
    }
};

class Solution {

    void reverse(string &s, int start, int end, int size) {
	int p = start;
	int q = end;

	if (start == end)
		return;

	if ((end - start) > size) {
		while (size) {	
			s.at(p) = s.at(p)^s.at(q);
			s.at(q) = s.at(p)^s.at(q); 
			s.at(p) = s.at(p)^s.at(q);
			p++;
			q--;
			size--;
		}
	} else {
		while (p < q) {	
			s.at(p) = s.at(p)^s.at(q);
			s.at(q) = s.at(p)^s.at(q); 
			s.at(p) = s.at(p)^s.at(q);
			p++;
			q--;
		}
	}
	
    }	

    public :
	
    void reverseWords(string &s) {
	int mark   = 0;   // start var in case of leading zeros
	int start  = 0;   // word start
	int end    = 0;   // word end
	bool bFlag = false;

	int len = s.length();

	if (!len)
		return;

	reverse(s, 0, len-1, len);

	for (int i = 0; i < len; i++) {
		char c = s.at(i);
		if (c == ' ' && bFlag) {
			bFlag = false;
			int size = end - start + 1;
			if ( mark < start) {
				reverse(s, mark, end, size);
				mark = mark + size + 1;
			} else {
				reverse(s, start, end, size);
				mark = start + size + 1;
			}	
			start = -1;
			end   = -1;
		} else if (c == ' ')  {
			continue;
		} else if (bFlag) {
			end = i;
			continue;
		} else {
			start = end = i;
			bFlag = true;
		}
	}
	
	if (bFlag) {
		int size = end - start + 1;
		if ( mark < start) {
			reverse(s, mark, end, end - start + 1);
			mark = mark + size + 1;
		} else {
			reverse(s, start, end, end - start + 1);
			mark = start + size + 1;
		}
			
	}

	if (mark)
		s = s.substr(0, mark - 1);
	else 
		s = s.substr(0, mark);
    }		
};
	

class Solution2 {

    bool isLetter(char c) {
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c >= '1' && c <= '9'))
		return true;
	else
		return false;
    }	
		
    void reverse(string &s, int start, int end) {
	int p = start;
	int q = end;

	while (p < q) {
		s.at(p) = s.at(p)^s.at(q); 
		s.at(q) = s.at(p)^s.at(q);
		s.at(p) = s.at(p)^s.at(q);
		p++;
		q--;
	}
    }	

public:

    void reverseWords(string &s) {
	
	string result = "";

	if (s.empty())
		return;

	reverse(s, 0, s.length() - 1);

	int start, end, pos, words;
	start = end = pos = words = 0;

	bool bFlag = false;
	bool check;

	for (auto p : s) {
		if ((check = isLetter(p)) && bFlag) {
			end = pos;	
		} else if (check) {
			start = pos;
			bFlag = true;
		} else if (bFlag) {
			bFlag = false;
			reverse(s, start, end);
			words++;
		}
		pos++;
	}

	if (words)	
		reverse(s, start, end);

	check = bFlag = false;
	string ans = "";
	for (auto p : s) {
		if ((check = isLetter(p)) && bFlag) {
			ans.append(1, p);	
		} else if (check) {
			ans.append(1, p);	
			bFlag = true;
		} else if (bFlag) {
			bFlag = false;
		}
	}

	s = ans;
    }

};

int main(void) {
	//string s ="blue boy";
	//string s ="1  1";
	//string s ="1    ";
	//string s ="     1";
	//string s ="     1  ";
	//string s =" 1       ";
	string s ="one. +two three? ~four !five- ";
	Solution1 *sol = new Solution1;
	Timer *t = new Timer();
	sol->reverseWords(s);
	double delta = t->elapsed();
	cout << s << endl;
	cout << delta << endl;
	return 0;
}
