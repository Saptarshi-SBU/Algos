#include <iostream>
#include <cassert>
#include <errno.h>

#define E_OK 0

struct Node {
	int   val;
	Node *next;
	
	Node(int v) : val(v), next(0) {}
};

typedef struct Node Node;

class Linklist {


	public :
		
		Node *head;

		Linklist(Node *node) : head(node) {}

	       ~Linklist() { delete head; }

		int size(Node *node);

		void append(Node *node);

		void add_to_tail(Node *node);
		
		void insert(Node *node,  Node *prev);

		void print(void);

		Node* search(int key);

		void remove(Node *node);
		
		Node *middle(void);

		Node *reverse(Node *node, int n);

		bool loop(Node *node);

		Node *getNthNode(Node *node, int n);

		void group_reverse(Node *node, int k);

		Node *group_alternate_reverse(Node *node, int n);

		bool *ispalimdrome(Node *node);

		Node *sort(Node *node);

		Node *isort(Node *node);

		Node *qsort(Node *node);

		Node *remove_lesser_nodes(Node *node);

		Node *rotate_link_list(Node *node);

		Node *removeLoop(Node *node);

		Node *union_op(Node *node1, Node *node2);

		Node *intersect_op(Node *node1, Node *node2);

		Node *dnf(Node *head);
};

void
Linklist::append(Node *node) {
	node->next = Linklist::head;
	Linklist::head = node;
	return;
}

void
Linklist::add_to_tail(Node *node) {
	Node *current = 0;

	for (current = Linklist::head; current->next; current = current->next) {
		current= current->next;
	}
	current->next = node;	
	node->next = NULL;
	return;
}

void
Linklist::insert(Node *node, Node *prev) {
	node->next = prev->next;
	prev->next = node;
	return; 
}

void
Linklist::remove(Node *node) {
	Node *current = 0;
	Node *prev    = 0;

	if (Linklist::head == node) {
		Linklist::head = Linklist::head->next;
		node->next = 0;
		goto done;
	}

	for (current = Linklist::head; current; prev = current, current = current->next) {
		if (node == current) {
			prev->next = current->next;
			current->next = 0;
			goto done;
		}
	}

done:
	delete node;
	return;
}

void 
Linklist::print(void) {
	Node *current;
	
	for (current = Linklist::head; current; current = current->next) 
		std::cout << current->val << "->";

	std::cout << "Null" <<  std::endl;
}	

struct Node*
Linklist::middle(void) {

	Node *slow = Linklist::head;
	Node *fast = Linklist::head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

Node*
Linklist :: reverse(Node *node, int n) {

	int   i = 0;
	Node *current;
	Node *prev_dg01;
	Node *prev_dg02;	

	if (!node) 
		return 0;

	if (!node->next)
		return node;

	if (!node->next->next) {
		current = node->next;
		current->next = node;
		node->next = 0;
		return current;
	}

	prev_dg02 = node;
	prev_dg01 = prev_dg02->next;

	if (prev_dg02 == Linklist::head) {
		prev_dg02->next = 0;
	}
	
	current   = prev_dg01->next; 
	i++;
	
	while(i < n && current) {

		prev_dg01->next = prev_dg02;
		prev_dg02 = prev_dg01;	
		prev_dg01 = current;
		current   = current->next;
		i++;
	};

	prev_dg01->next = prev_dg02;

	return prev_dg01;
}

Node *
Linklist :: getNthNode(Node *node, int n) {
	int   i = 0;
	Node *curr = node; 

	for (; i < n &&  curr->next; curr = curr->next, ++i) ;
	return curr;
}

void
Linklist :: group_reverse(Node *node, int k) {
	
	Node *curr_block_head, 
	     *revr_block_head,
	     *curr_block_rear,
	     *prev_block_rear,
	     *next_block_head;


	curr_block_head = node;
	next_block_head = Linklist::getNthNode(curr_block_head, k + 1);
	revr_block_head = Linklist::reverse(curr_block_head, k);
	curr_block_head->next = 0;

	if (Linklist::head == node) {
		Linklist::head = revr_block_head;
	}

	while (curr_block_head != next_block_head) {
		prev_block_rear = curr_block_head;	

		// reverse the next block
		curr_block_head = next_block_head;
		next_block_head = Linklist::getNthNode(curr_block_head, k + 1);

		revr_block_head = Linklist::reverse(curr_block_head, k);
		curr_block_head->next = 0;

		// link the new reversed block to the previous
		prev_block_rear->next = revr_block_head;
	};
	
	return;	
}

Node*
Linklist::group_alternate_reverse(Node *node, int n) {
	Node *curr,*post,*prev = 0, *next;
	int i = 0;

	if ((!node)  && (!n))
		return 0;

	curr = node;
	i = 0;
	while (curr && i < n) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		i++;
	}
	
	node->next = curr;

	i = 0;
	while(curr && i < n-1) {
		curr = curr->next;
		i++;
	};

	if (curr)
		curr->next = group_alternate_reverse(curr->next, n);
	return prev;
}

//Great Tree recursion 
int main(void) {
	int i;

	Linklist list(new Node(0));

	for (i = 1; i < 10; i++) 
		list.append(new Node(i));

	list.print();

	list.insert(new Node(100), list.head);

	list.insert(new Node(101), list.head);

	list.print();

	list.remove(list.head);

	list.remove(list.head);

	list.print();

	list.head = list.reverse(list.head, 10);

	list.print();

	std::cout << "Middle Node " << list.middle()->val << std::endl;	

	//for (i = 1; i < 10; i++) 
	//	std::cout << (list.getNthNode(list.head, i))->val << std::endl;

	list.group_reverse(list.head, 3);

	list.print();

	list.group_reverse(list.head, 3);

	list.print();

	list.head = list.group_alternate_reverse(list.head, 3);

	list.print();

	return 0;

}
