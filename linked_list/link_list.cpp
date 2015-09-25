#include <iostream>
#include <errno.h>

#define E_OK 0

struct Node {
	int   val;
	Node *next;
};

typedef struct Node Node;

class Linklist {

	Node *head;

	public :

		Linklist(Node *node);

	       ~Linklist();

		int size(Node *node);

		int append(int key);
		
		int insert(int key, int pos);

		int remove(int pos);
		
		Node *middle(Node *node);

		Node *reverse(Node *node);

		bool loop(Node *node);

		Node *group_reverse(Node *node);

		Node *group_alternate_reverse(Node *node);

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

class FastLinklist {
	Node *head;

	public :
		Node *insert_op(Node *node);

		Node *delete_op(Node *node);

		Node *search(Node *node);

};

int
Linklist::append(int key) {

	Node *node = new Node;

	if (0 == node) 
		return -ENOMEM;

	node->val = key;

	Node *current;
	
	if (!Linklist::head) 
		return -EINVAL;	

	current = Linklist::head;

	while (current->next) {
		current= current->next;
	};

	current->next = node;	
	node->next = NULL;
	return E_OK;
}

int
Linklist::insert(int key, int n) {
	int   i;
	Node *current = Linklist::head;

	Node *node = new Node;
	if (NULL == node) {
		return -ENOMEM;
	}

	node->val = key;

	if (!Linklist::head) {
		Linklist::head = node;
		return E_OK;
	} else {
		current = Linklist::head;
	}

	for (i = 0; i < n && current->next; i++) {
		current = current->next;
	}

	node->next = current->next;
	current->next = node;
		
	return E_OK;
}

int
Linklist::remove(int n) {
	int i = 0;
	Node *temp;
	Node *current = Linklist::head;

	if (!current) {
		return -EINVAL;
	}

	if (n > Linklist::size(head)) {
		return -EINVAL;
	}	

	while (i < n-1) {
		current = current->next;
		i++;
	};

	temp = current->next;
	current->next= temp->next;
	delete temp;
	return E_OK;
}

//Great Tree recursion 
int main(void) {








}
