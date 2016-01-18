#include <iostream>
#include <cassert>
#include <errno.h>

#define E_OK 0

using namespace std;

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
		
		Node* Kreverse(Node *node, int k, int flag);
		
		//reverse a link list
		void preverse(Node *curr);
		
		void preverse_iterative(void);
		
		Node *reverse_group(Node *node, int count);
		
		int swapN();

        Node *pairwise_swap(Node *node);
        
        Node *merge_list(Node *p, Node *q);
};

Node*
Linklist::merge_list(Node *p, Node *q) {
    
    if ((!p) && (!q))
        return 0;
        
    if (!p)
        return q;
        
    if (!q)
        return p;
        
    if (p->val >= q->val) {
        p->next = merge_list(p->next, q);
     //   cout << "p " <<  p->val << " " << q->val << endl;
        return p;
    }  else { 
        q->next = merge_list(p, q->next);
     //   cout << "q " << q->val << endl;
        return q;
        
    }   
}

Node* 
Linklist::pairwise_swap(Node *node) {
    
    if (!node) {
        return 0;
    }
    
    Node *p = node;
    if (!p->next)
        return p;
        
    Node *q = p->next;
    
    Node* q_next = q->next;
    p->next->next = p;
    p->next = pairwise_swap(q_next);
    return q;
}

#if 0

//1 2 3 4 5 6 7

int
Linklist::swapN(int n) {
    
    Node *p, p_prev;
    Node *q, q_prev;
    
    int i = n;
    p = head;
    p_prev = 0;
    
    if (n <=0)
        return -1;
        
    while (p && i < n - 1) {
        p_prev = p;
        p = p->next;
        i++;
    }
    
    if (!p) 
        return -1;
    
    Node *fp, *sp;
    fp = sp = head;
        
    while (sp && sp->next && i < n - 1) {
        sp = sp->next;    
    }
   
    while(sp->next) {
          q_prev = fp;
          fp = fp->next 
          sp = sp->next;  
    } 
    
    q = fp;
    
    if (!p_prev) {
        Node *temp = q->next;
        q->next = p->next;
        p->next = temp;
        q_prev->next = p;
        
    } else if (!q_prev) {
        Node *temp = p->next;
        p->next = q->next;
        p_prev->next = q;
        q->next = temp;
        
    } else {
        Node *temp = p->next;
        p_prev->next = q;
        p->next = q->next;
        q_prev->next = p;
        q->next = temp;
    }    
}

#endif

//1 2 3 4 5 6 7
//3 2 1 6 5 4 7

//last->next : front->next
//reverse_give_new_head

Node*
Linklist::reverse_group(Node *node, int count) {
    
    Node *p, *q, *r;
    
    int k = 0;
    
    if (!node)
        return 0;
        
    p = node;
    
    if (!p->next)
        return p;
        
    q = p->next;
    
    r = 0;
    
    while (k < count) {
        p->next = r;
        r = p;
        p = q;
        if (!p)
            break;
        q = q->next;
        k++;
    }; 
    
    node->next = reverse_group(p, count);
    return r;
}

//L1->L2->L3
//4->100->8->Null
    
void 
Linklist::preverse(Node *curr) {
    
    if (!curr)
        return;
    
    if (!curr->next) {
        head = curr;
        return;
    }    
        
    preverse(curr->next);
    curr->next->next = curr;
    curr->next = 0;
    
    return;
} 

//1 2 3 4 5
void
Linklist::preverse_iterative() {
    
    Node *p, *q, *r;
    
    if (!p)
        return;
        
    p = head;
        
    if (!p->next)
        return;
        
    q = p->next;
    
    r = 0;
    
    while (!p) {
        p->next = r;
        r = p;
        p = q;
        q = q->next;
    }
    
    head = r;
    return;
}

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

Node* 
Linklist::Kreverse(Node *head, int k, int flag) {

    //
    // 1->2->3->4->5
    //
    
   int count = 0; 
   
   Node *prev = 0;
   Node *curr = head;
   Node *succ = 0;
   
   if (!head)
        return 0;
        
   if (flag == 0) {
   while (curr && count < k) {
       succ = curr->next;
       curr->next = prev;
       prev = curr;
       curr = succ;
       count++;
    };    

    head->next = Kreverse(curr, k, 1);
   } else {
       
    while (curr && count < k) {prev = curr; curr = curr->next; count++;}
  
    curr->next = Kreverse(curr->next, k, 0);
   }
   
   return prev;
}

//Great Tree recursion 
int main(void) {
	int i;

	Linklist list(new Node(0));

	for (i = 1; i < 10; i++) 
		list.append(new Node(i));

	Linklist list2(new Node(0));

	for (i = 1; i < 10; i++) 
		list2.append(new Node(i));
		
	list.head = list.merge_list(list.head, list2.head);
	

	list.print();
//	list2.print();
	#if 0 
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

//	list.group_reverse(list.head, 3);
    
//    list.head = list.Kreverse(list.head, 3, 1);
    
//	list.print();
	
	list.preverse(list.head);
	
	list.print();
	
	list.preverse_iterative();
	
	list.head = list.reverse_group(list.head, 3);
	
	list.print();

    list.head = list.pairwise_swap(list.head);
    
    list.print();
    
    list.head = list.merge_list(list.head, list2.head);
    
	//list.head = list.group_alternate_reverse(list.head, 3);

	//list.print();
    #endif
	return 0;

}
