/*--------------------------------------------------------------------
 *
 * remove duplicates from a Link List
 *
 *-------------------------------------------------------------------*/

#include <iostream>

typedef struct LinkListNode {
	int data;
	LinkListNode *next;
}LinkListNode;

using namespace std;

class LinkList {

	public :

		LinkListNode *head_;
		size_t size_;


		LinkList(int n) {
			head_ = new LinkListNode;
			head_->data = n;
			head_->next = 0;
			size_++;
		} 

		~LinkList() {

			LinkListNode *temp;

			while (head_ != NULL) {
				temp  = head_;
				head_ = head_->next;
				delete temp;
				size_--;
			}		
		}

		void append(int n) {

			LinkListNode *temp = head_;

			while (temp->next != 0) {
				temp = temp->next;
			}

			temp->next = new LinkListNode;
			temp = temp->next;

			temp->data = n;
			temp->next = 0;

			size_++;
		}	

		void print(void) {

			int i = size_;
			LinkListNode *temp = head_;

			while (temp) {
				std::cout << temp->data << std::endl;
				temp = temp->next;
			}
		}

		int count_length(LinkListNode *node) {
			int i = 0;
			for (; node; node = node->next, i++);
			return i;
		}

		LinkListNode *nth_node_last(LinkListNode *node, int* n) {
			if (!node)
				return 0;
			LinkListNode *nth_node = nth_node_last(node->next, n);
			if (!--*n)
				return node;
			else
				return nth_node;
		}

		LinkListNode *nth_node_last(LinkListNode *node, int n) {
			int i;

			LinkListNode *p = node;
			LinkListNode *q = node;

			if (n <=0)
				return 0;

			for(i=0; q && i < n - 1;q = q->next,i++);

			if (!q)
				return 0;

			while (q->next) {
				p = p->next;
				q = q->next;
			}

			return p;
		}

		LinkListNode *find_middle(LinkListNode *node) {
			LinkListNode *p = node;
			LinkListNode *q = node;

			while (q && q->next) {
				p = p->next;
				q = q->next->next;
			}
			return p;
		}

		LinkListNode *findNthnode(int n) {
			if (n <=0)
				return 0;	
			LinkListNode *p = head_;
			for (;p && n - 1;n--, p=p->next);
			return p;
		}

		bool remove_loop() {

			bool found = false;

			LinkListNode *p = head_;
			LinkListNode *q = head_;

			while (q && q->next) {
				p=p->next;
				q=q->next->next;
				if (p == q) {
					found = true;
					break;
				}
			}

			if (found) {

				int n = 0;
				do {
					q = q->next;
					n++;
				} while (p != q);

				cout << "Loop length " << n << endl;

				p = q = head_;
				for(;n - 1;n--)
					q = q->next;
				
				for (; p != q->next; p=p->next, q = q->next);
				q->next = 0;
			}

			return found;	
		}
};

int main(void) {

	LinkList *listA = new LinkList(100);
	listA->append(101);
	listA->append(102);
	listA->append(101);
	listA->append(103);
	listA->append(113);
	int n = listA->count_length(listA->head_);
	//listA->print();	
	n = 6;
	LinkListNode *node = listA->nth_node_last(listA->head_, &n);
	if (node)
		cout << node->data << endl;
	n = 6;
	node = listA->nth_node_last(listA->head_, n);
	if (node)
		cout << node->data << endl;
	#if 0
	node = listA->find_middle(listA->head_);
	cout << node->data << endl;	
	node->next = listA->head_;
	listA->remove_loop();
	listA->print();	
	#endif

	cout << listA->findNthnode(6)->data << endl;
	cout << listA->findNthnode(3)->data << endl;		

	LinkListNode *p = listA->findNthnode(4);
	LinkListNode *q = listA->findNthnode(1);
	p->next = q;
	//listA->print();	
	listA->remove_loop();
	listA->print();	
	
	
	return 0;
}

