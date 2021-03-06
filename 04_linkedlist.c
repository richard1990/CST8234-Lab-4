/**************************************************************************
 * PROGRAM		04_linkedlist.c
 * AUTHOR		Richard Barney
 * DATE			October 2013
 * NOTES		This program is a simple linked list making use of
 *			a struct that has an int and a pointer for a next
 *			memory allocation.
 **************************************************************************/

/**************************************************************************
 *  Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
 * Function prototypes
 **************************************************************************/
struct node {
	int data;
	struct node* next;
};
int Length(struct node* head);
void PrintList(struct node* head);
void Add(struct node** headRef, int new);
int Delete(struct node** headRef);
void ZeroList(struct node** headRef);

/**************************************************************************
 * main
 **************************************************************************/
int main(void) {
	struct node* head = NULL;
	int num, ret;
	char select = 'n';
	char c;
	/* display welcome message */
	printf("Welcome to Richard's Simple Linked List!\n");
	/* loop until user enters e or EOF */
	while (select != 'e' || select != 'E' || ret != EOF) {
		printf("Enter:\n");
		printf("a(dd) (x) = add a new node with value \"x\" to the list ");
		printf("at the front of the list\n");
		printf("d(el) = delete the first node of list\n");
		printf("l(ength) = print the number of nodes in the list\n");
		printf("p(rint) = print the complete list\n");
		printf("z(ero) = delete the entire list\n");
		printf("e(xit) = quit the program\n");	
		/* use fscanf per lab requirements */
		ret = (fscanf(stdin, "%c", &select));
		/* to make the menu display somewhat properly, I had to make 
		 * sure the user entered the [enter] key after entering a
		 * number, otherwise the menu would display itself twice 
		 * because it took another input after the number, which is why
		 * I check if c == the new line char. Unfortunately, this 
		 * method is not foolproof because if the user enters stuff 
		 * after the number, then the menu displays itself multiple
		 * times. */
		if (ret == EOF) {
			break;
		}
		/* if "a" was entered, then add a new node with the value
		 * entered */
		if (select == 'a' || select == 'A') { 
			ret = (fscanf(stdin, "%d%c", &num, &c));	
			if (c == '\n') {
				Add(&head, num);
			}
		}
		else {
			/* read input, which should be the newline char */
			fscanf(stdin, "%c", &c);
			if ((select == 'd' && c == '\n') || (select == 'D' && c == '\n')) {
				Delete(&head);
			}			
			else if ((select == 'l' && c == '\n') || (select == 'L' && c == '\n')) {
				printf("There are %d node(s).\n\n", Length(head));
			}
			else if ((select == 'p' && c == '\n') || (select == 'P' && c == '\n')) {
				PrintList(head);
			}
			else if ((select == 'z' && c == '\n') || (select == 'Z' && c == '\n')) {
				ZeroList(&head);
			}
			else if ((select == 'e' && c == '\n') || (select == 'E' && c == '\n')) {
				break;
			}
			else {
				printf("Invalid input! Please try again.\n\n");
			}
		}
	}	
	return EXIT_SUCCESS;
}

/**************************************************************************
 * Function: void Add(struct node** headRef, int new)
 * given an int and a reference to the head pointer (i.e. a struct node**
 * pointer to the head pointer), add a new node at the head of the list
 **************************************************************************/
void Add(struct node** headRef, int new) {
	struct node* n;
	/* allocate memory for new node */
	n = (struct node*) malloc(sizeof(struct node));
	/* give new node the int entered by user */
	n -> data = new;
	n -> next = *headRef;
	*headRef = n;
	printf("New node created.\n\n");
	return;
}

/**************************************************************************
 * Function: int Delete(struct node** headRef)
 * takes a non-empty list, deletes the head node, and returns the head 
 * node's data
 **************************************************************************/
int Delete(struct node** headRef) {
	struct node* old;
	int value = 0;
	/* if the head is NULL, tell user there is nothing to delete */
	if (*headRef == NULL) {
		printf("Head is NULL! Nothing to delete!\n\n");
		return value;
	}
	old = *headRef;
	value = old -> data;
	*headRef = old -> next;
	free(old);
	printf("The head has been deleted.\n\n");
	return value;
}

/**************************************************************************
 * Function: void PrintList(struct node* head)
 * prints all the nodes on a list
 **************************************************************************/
void PrintList(struct node* head) {
	struct node* current = head;
	/* if current is NULL, tell the user there is nothing to display */
	if (current == NULL) { 
		printf("Nothing to display because the linked list is empty!\n\n");
		return;
	}
	/* go through the nodes until current equals NULL and print the int values */
	while (current != NULL) {
		printf("%d -> ", current -> data);
		current = current -> next;
	}
	printf("NULL\n\n");
	return;
}

/**************************************************************************
 * Function: int Length(struct node* head)
 * returns the number of nodes in the list
 **************************************************************************/
int Length(struct node* head) {
	struct node* current = head;
	int count = 0;
	/* count the number of nodes until current equals NULL (the head) */
	while (current != NULL) {
		count++;
		current = current -> next;
	}
	return count;
}

/**************************************************************************
 * Function: void ZeroList(struct node** headRef)
 * deallocates all of its memory and sets its head pointer to NULL (the 
 * empty list)
 **************************************************************************/
void ZeroList(struct node** headRef) {
	struct node* old;
	/* if head is NULL, tell user theres nothing to do */
	if (*headRef == NULL) {
		printf("Nothing to free because the linked list is empty!\n\n");
		return;
	}
	/* as long as head is not NULL, delete every single node */
	while (*headRef != NULL) {
		old = *headRef;
		*headRef = old -> next;
		free(old);
	}
	printf("All nodes have been deleted.\n\n");
	return;
}
