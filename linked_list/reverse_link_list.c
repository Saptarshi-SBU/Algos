#include <stdio.h>

typedef struct node {
	int val;
	struct node *next;
}node;	

node *
sll_last(node *front, int nodes_count) {

	node *temp = front;
	
	for( i = 0; i < nodes_count; i++, temp = temp->next);
	  
	return temp;	
}

node *
sll_reverse(node *front, node *rear) {
	
	node *np0 = front;
	node *np1 = front->next, 
	node *np2 = 0;
	
	do {
		np2 = np1->next;
	
		np1->next = np0;

		if ( np0 == front) {
			np0->next = 0;
		}

		np0 = np1;
		np1 = np2;
		
	} while ( np1 != rear);

	rear  = front;
	front = np1;

	return np2;
}

static void 
sll_main(node *head, int terms) {
	node *front, *rear;

	if ( head ) {
		front = head;
	} else {
		return;
	}

	do {
		rear  = sll_last(front, terms);
		if ( !rear ) {
			return;
		}

		last  = sll_reverse(front, rear);
		if (last) {
			rear->next = last;
		}
		
		front = rear;
	} while ( front );  
}

int main( void ) {






}
