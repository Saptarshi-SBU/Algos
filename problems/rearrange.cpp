/*-------------------------------------------------------------------------
 *
 *  re-arrange
 *  
 *------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, int> table_;

struct node {
	
	node(char p, int freq) : p_(p), freq_(freq) {}
       ~node() {}

	char p_;
	int  freq_;
};

vector<node*> v;

node *temp, *temp2;

int main(int argc, char **argv) {

	if (argc != 2)
		return -1;

	string s;

	string str(argv[1]);

	char prev = '0'; // sentinel

	for (auto i : str)
		table_[i]++;

	for (auto i : table_)
		v.push_back(new node(i.first, i.second));

	make_heap(v.begin(), v.end(), [](node* p, node* q) { return p->freq_ < q->freq_;});

	while (v.size()) {
		pop_heap(v.begin(), v.end(), [](node* p, node* q) { return p->freq_ < q->freq_;});
		temp = v.back();
#if 1
		if (prev != '0' && prev == temp->p_) {
			v.pop_back();
			if (!v.size())
				goto error;
			pop_heap(v.begin(), v.end(), [](node* p, node* q) { return p->freq_ < q->freq_;});
			temp2 = v.back();
			v.pop_back();

			prev = temp2->p_;
			s.append(sizeof(char), temp2->p_);
			temp2->freq_--;
			if (temp2->freq_) {
				v.push_back(temp2);
			}

			v.push_back(temp);
			push_heap(v.begin(), v.end(), [](node* p, node* q) { return p->freq_ < q->freq_;});
			continue;
		}
		prev = temp->p_;
		s.append(sizeof(char), temp->p_);
		v.pop_back();
		temp->freq_--;
		if (temp->freq_) {
			v.push_back(temp);
			push_heap(v.begin(), v.end(), [](node* p, node* q) { return p->freq_ < q->freq_;});
		}
#endif		
	}

	cout << s << endl;
	return 0;

	error:
	cout << "invalid string " << endl;
	return -1;
}
