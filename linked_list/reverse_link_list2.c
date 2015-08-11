#include <stdio.h>

node * 
sll_reverse(node *cur, node *prev) {
	
	node *node = 0;

	if (cur && cur->next == 0) {
		return cur;
	}

	node = sll_reverse(cur->next, cur);
	cur->next = prev;
	return node;
}

int 
sll_main(void) {
	
	node *head  = sll_reverse(front, front->next);
	return;
}	
	
		
	





}
