/*************************************************************************************************
  Programs for Linked Lists
  -- Create a node
  -- Insert a node in linked list
  --Head
  --End
  --nth position
  -- Delete a node
  --Head node
  --Last node
  --nth node
  -- Swap nodes without the swapping data
  -- Reverse a linked list
  -- Merge linked list


 **************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next; 
};

// the function to print or display the linked list 
void printLinkList (struct node *head)
{
	struct node *nextnode;

	nextnode = head;
	printf("\nLinked list now \n");

	while (nextnode != NULL)
	{
		printf("%d \t",nextnode->data);
		nextnode = nextnode->next;
	}

}

/* The parameter position will give the position number where new node is to be inserted

   -> 0    the head or beginning of linked list
   -> +ve  the nth position eg. 4th position ,5th position etc
   -> -ve  the tail end of the linked list i.e append to the end of list
   */
void insertnode (struct node **head, int newdata , int position)  // the function type is struct node* because the pointer to new head is returned to main
{
	int count =0 ;
	struct node *current = *head , *newnode;


	newnode = (struct node*)malloc(sizeof (struct node));
	newnode->data = newdata;

	if (position >= 0)
	{
		while (count < position)
		{
			count ++;
			current = current->next;
		}

		if (count==position)
		{

			newnode->next = current;
			if (position ==0)
			{
				*head = newnode ;

			}
		}
	}

	else
	{
		while (current->next!= NULL)
		{
			current = current->next;
		}

		current->next = newnode;
		newnode->next = NULL;

	}

	//return head;
}

#define PANIC(str) printf(str); \
	abort();


int 
find_previous(struct node *head, 
		int key, 
		struct node **key_node) {

	struct node *iterator = head;

	if (iterator->data == key) {
		*key_node = 0;
		return 0;
	}

	while (iterator && iterator->next) {
		if (iterator->next->data == key) {
			*key_node = iterator;
			return 0;
		} else {
			iterator = iterator->next;
		}		;
	}

	return -1;
}


	void 
swapnode (struct node **head, int x, int y)
{
	int ret = 0;

	struct node *node_x = 0;
	struct node *prev_x = 0;
	struct node *next_x = 0;

	struct node *node_y = 0; 
	struct node *prev_y = 0;
	struct node *next_y = 0;

	if (!*head) {
		PANIC("invalid head");
	}

	ret = find_previous(*head, x, &prev_x);
	if (ret < 0) {
		PANIC ("key not found!");
	}

	ret = find_previous(*head, y, &prev_y); 
	if (ret < 0) {
		PANIC( "key not found!");
	}

	node_x = prev_x ? prev_x->next : *head;
	next_x = node_x->next;

	node_y = prev_y ? prev_y->next : *head;
	next_y = node_y->next;

	if (node_x == node_y) {
		return;
	}

	// use case : if swapped nodes form a pair
	if (node_x->next == node_y) {
	
		if (prev_x)	
			prev_x->next = node_y;
		node_y->next = node_x;
		node_x->next = next_y;

	} else if (node_y->next == node_x) {
		
		if (prev_y)	
			prev_y->next = node_x;
		node_x->next = node_y;
		node_y->next = next_x;

	// use case : if swapped nodes do not form a pair
	} else {

		if (prev_x)	
			prev_x->next = node_y;
		node_y->next = next_x;

		if (prev_y)	
			prev_y->next = node_x;
		node_x->next = next_y;
	}

	// spl use case : if a node is a head
	
	if (!prev_x) {
		*head = node_y;
	} else if (!prev_y) {
		*head = node_x;
	}

}

int 
LinkListloopExist(struct node *head, size_t size) {

	int  i = (int) size;

	struct node *iterator = head;

	for ( i = 0; i < (int)size; i++) {
		if (!iterator) 
			return -1;
		iterator = iterator->next;
	}

	if (iterator)
		return -1;
	else 
		return 0;
}

#define DEBUG 0

int main ()
{
	struct node  *head;

	struct node  *temp = 0;

	size_t size  = 0;

	head = (struct node*)malloc(sizeof(struct node)); //allocate space and return address for the head node


	//initiate head node with data

	head->data = 1;
	head->next =NULL;
	size++;

	//printLinkList(head);

	//head =
	insertnode(&head , 0, 0);
	size++;
	// head = 
	insertnode(&head , 2, -1);
	size++;
	// head = 
	insertnode(&head , 3, -1);
	size++;

	insertnode(&head , 4, -1);
	size++;

	insertnode(&head , 5, -1);
	size++;

	printLinkList(head);

#if DEBUG

	if (0 == find_previous(head, 0, &temp)) {
		printf ("Found element\n");
		if (temp) 
			printf("previous is %d\n", temp->data);
	} else {
		printf ("element not found\n");
	}

#endif

	//swapnode(&head , 1, 2);
	swapnode(&head , 1, 3);

	if (LinkListloopExist(head, size) < 0) {
		PANIC("loop!");
	} else {
		printLinkList(head);
	}

	return 0;

}


