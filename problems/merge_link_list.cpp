/*--------------------------------------------------------------------
 *
 * Sort Link List using Merge Sort
 *
 * 
 *
 *-------------------------------------------------------------------*/

#include <iostream>

typedef struct LinkListNode {
	int data;
	LinkListNode *next;
}LinkListNode;

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

};

LinkListNode*
Merge(LinkListNode *p, LinkListNode *q) {

	if (!p) {

		return q;

	} else if (!q) {

		return p;

	} else if (p->data > q->data) { 

		q->next = Merge(p, q->next); 
		return q;	

	} else {

		p->next = Merge(p->next, q);
		return p;
	}	

}

int main(void) {

	LinkList *listA = new LinkList(100);
	listA->append(101);
	listA->append(102);
	listA->append(103);
	listA->append(113);
	//listA->print();	

	LinkList *listB = new LinkList(98);
	listB->append(99);
	listB->append(107);
	listB->append(109);
	//listB->print();	

	listA->head_ = Merge(listA->head_, listB->head_);
	listA->print(); 

	return 0;
}

