#include <stdio.h>

bool
sll_palimdrome(node *rear, node **front) {
	if (!rear) 
		return 0;
	sll_palimdrome(rear->next, front); 
	if (rear->val == (*front)->val) {
		*front = (*front)->next;
		return 0;
	} else {
		return -1;
	}
}

int main(void) {

	bool b = sll_palimdrome(front->next, &front);
	if (b)
		return 1;
	else
		return -1;
}
