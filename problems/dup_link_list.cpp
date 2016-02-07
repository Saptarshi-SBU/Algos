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

		LinkListNode *nth_node(LinkListNode *node, int n) {
			for (int i = 0; node && i < n; i++)
				node = node->next;
			return node;
		}

		LinkListNode *merge_duplicate(LinkListNode *p, LinkListNode *q) {

			if ((!p) && (!q)) {
				return 0;
			} else if (!p) {
				return q;
			} else if (!q) {
				return p;
			} else	{
				if (p->data == q->data) {
					LinkListNode *temp = q;
					q = q->next;
					delete temp;
					merge_duplicate(p, q->next);
					return p;
				} else if (p->data < q->data) {
					p->next = merge_duplicate(p->next, q);
					return p;
				} else if (p->data > q->data) {
					q->next = merge_duplicate(p, q->next);
					return q;
				}
			}
		}


		LinkListNode *remove_duplicate2(LinkListNode *p, int n) {

			if (!n)
				return p;

			LinkListNode *node = nth_node(p, n/2);	
			LinkListNode *q = 0;
			if (node) {
				q = node->next;
				node->next = 0;
				remove_duplicate2(p, n/2);
				remove_duplicate2(q, n - n/2);
			}
			return merge_duplicate(p, q);
		}

		LinkListNode *remove_duplicate(LinkListNode *p, int low , int high) {

			if (low == high)
				return p;

			int mid = (low + high)/2;

			LinkListNode *node = nth_node(p, mid - low);	
			LinkListNode *q = 0;
			if (node) {
				q = node->next;
				node->next = 0;
				remove_duplicate(p, low, mid);
				remove_duplicate(q, mid + 1, high);
			}
			return merge_duplicate(p, q);
		}
};

int main(void) {

	LinkList *listA = new LinkList(100);
	listA->append(101);
	listA->append(102);
	listA->append(101);
	listA->append(103);
	listA->append(113);
	//listA->print();	
	int n = listA->count_length(listA->head_);
	//listA->head_ = listA->remove_duplicate(listA->head_, 0, n - 1);
	listA->head_ = listA->remove_duplicate2(listA->head_, n);
	listA->print();	
	return 0;
}

