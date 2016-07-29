#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
//clients

typedef struct {
    char firstName[50];
    char lastName[50];
    char number[10];
} Client;
// define the data structure of a node

typedef struct node {
    Client clients;
    struct node *next;
} Node, *NodePtr;

// define a struct for the linked list 

typedef struct {
    NodePtr first, np, last;
} LinkedList;

// define the makenode function
// allocates memory, sets the node members, 
// and returns the address of the nof 

NodePtr makeNode(Client c) {
    // allocate memory to the node 
    NodePtr np = (NodePtr) malloc(sizeof (Node));
    // set the node members to the values
    strcpy(np->clients.firstName, c.firstName);
    strcpy(np->clients.lastName, c.lastName);
    strcpy(np->clients.number, c.number);

    np->next = NULL; //because it will be added to the last node
    return np;
}

/*load
creates a linked list
reads the file
every client becomes a node
close file
return node pointer

 */
void showall(NodePtr movingPtr) {
    while (movingPtr != NULL) { // as long as there is a node
        printf("\n first name: %s  last name :%s number: %s \n", movingPtr->clients.firstName,movingPtr->clients.lastName,movingPtr->clients.number);
        movingPtr = movingPtr->next; // go on to the next node
    }
}
LinkedList Load(void) {

    LinkedList myList;
    myList.first = NULL;
    FILE *in = fopen("phonebook.txt", "r");
    if (in == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (!feof(in)) {
        Client c;
        char fName[50];
        char lName[50];
        char num[10];
        fscanf(in, "%s %s %s", fName, lName, num);

        strcpy(c.firstName, fName);
        strcpy(c.lastName, lName);
        strcpy(c.number, num);
        myList.np = makeNode(c);
        if (myList.first == NULL) {
            myList.first = myList.np;
        } else {
            // make the current last node points to the new node
            myList.last->next = myList.np;
        }
        //update the last pointer
        myList.last = myList.np;

       

    }
 return myList;

}

/*
add
 */
void add(Client c, LinkedList myList) {
	printf("adding...\n");
    myList.np = makeNode(c);
	 if (myList.first == NULL) {
            myList.first = myList.np;
        } else {
            // make the current last node points to the new node
            myList.last->next = myList.np;
        }
        //update the last pointer
        myList.last = myList.np;

       


    printf("successfully added %s %s%s", c.firstName, c.lastName, "\'s number to the phonebook\n");
}

//Recursive process to break up all the linked list
void partition(NodePtr head, NodePtr *front, NodePtr *back){

    NodePtr fast;
    NodePtr slow;

    if (head == NULL || head->next == NULL){

        *front = head; // &a
        *back = NULL; // &b

    }else{

        slow = head;
        fast = head->next;

        while(fast != NULL){
            fast = fast->next;
            if(fast != NULL){
                slow = slow->next;
                fast = fast->next;
            }

        }

        *front = head; // a
        *back = slow->next; // b
        slow->next = NULL;
    }

}

//mergesort
NodePtr mergeLists(NodePtr a, NodePtr b){
    NodePtr mergedList = NULL;

    if (a == NULL){
        return b;
    }else if (b == NULL){
        return a;
    }

    if (strcmp(a->clients.lastName, b->clients.lastName) <= 0){
        mergedList = a;
        mergedList->next = mergeLists(a->next, b);
    }else{
        mergedList = b;
        mergedList->next = mergeLists(a, b->next);
    }

    return mergedList;

}


//Seperate Linked List than use mergesort to sort the linked list
void mergesort(NodePtr *client){
	NodePtr head = *client;
    NodePtr a = NULL;
    NodePtr b = NULL;

    if(head == NULL || head->next == NULL){
        return;
    }

    partition(head, &a, &b);

    mergesort(&a);
    mergesort(&b);

    *client = mergeLists(a, b);
}

//search function
void search(NodePtr movingPtr, char search[50]){
	int count = 0;
	NodePtr tempFirst = movingPtr;
	//while linked list is not null compare string with last name, if it matches print
	while(movingPtr != NULL){
		if(strcmp(search, movingPtr->clients.lastName) == 0){
			printf("\nFrist Name: %s\nLast Name: %s\nPhone Number: %s \n", 
				movingPtr->clients.firstName, movingPtr->clients.lastName, 
				movingPtr->clients.number);
			count++;
		}
		movingPtr=movingPtr->next;
	}
	//print if there is no matched result
	if(count == 0)
		printf("No Matched Result Found!\n");
	movingPtr=tempFirst;
}

//delete
//search function
void delete(NodePtr movingPtr, char search[50]){
	NodePtr tempFirst = movingPtr;
	while(movingPtr != NULL){
		if(strcmp(search, movingPtr->clients.lastName) == 0){
			tempFirst->next=movingPtr->next;
			free(movingPtr);
		}else{
		tempFirst = movingPtr;
		}
	movingPtr=movingPtr->next;
	}

}

//save function
/* This function save linked list to phonebook.txt
   Save function is called when you want to exit the program */
void save(LinkedList myList){
	FILE *in = fopen("phonebook.txt", "w");
	if (in == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	NodePtr movingpt;
	movingpt=myList.first;
	while(movingpt!=NULL){
		fprintf(in,"%s %s %s \n", 
		movingpt->clients.firstName, movingpt->clients.lastName, 
		movingpt->clients.number);
		movingpt=movingpt->next;
	}
}
//main

int main(int argc, char *argv[]) {
    //load linked list
    LinkedList myList;
	printf("-------------------------Loading---------------------------\n");
    myList = Load();
	mergesort(&myList.first);
	printf("\nLoading completed");
    //prompt for options
    int option;
    printf("\nselect 1 for inserting a new number to the phone book\nselect 2 to retrieve for a client's phone number\nselect 3 to delete an entry\nselect 4 to display all the numbers in the phone book\n select any other key to exit\noption:  ");
	scanf("%d", &option);
	
	//while you press right option menu it will asking menu
	while(0==0){
    //add fuction
	    if (option == 1) {
	        printf("\nyou selected the add function\n type cancel to...cancel\n");

	        Client c;
	        printf("enter first name: ");
	        scanf("%s", c.firstName);
	        //end if user enters cancel
	        if (strcmp(c.firstName, "cancel") == 0) {
	           continue;
	        }
	        printf("\nenter last name: ");
	        scanf("%s", c.lastName);
	        if (strcmp(c.lastName, "cancel") == 0) {
	            continue;
	        }
	        printf("\nenter number: ");
	        scanf("%s", c.number);
			int length = strlen (c.number);
			
	        for (int i=0;i<length; i++){
	        	if (!isdigit(c.number[i])){
					printf("\nyou have non-numerical characters in this number\n");	
					continue; 
				}
			}
				
	        if (strcmp(c.number, "cancel") == 0) {
	         continue; 
			}else{
	       		add(c, myList);
				mergesort(&myList.first);
	   		}
			//search
		}else if (option == 2) {
			printf("\nyou selected the search function\n");
			//if phonebook.txt file has no data and user select this function before adding
			//phonebook info print this message
			if(myList.first == NULL){
				printf("No data in phone book!\nPlease use Add menu before using this menu!\n");
			}else{
				int inputValid = -1;
				char userInput[50];
				//check userInput
				while(inputValid == -1){
					printf("Please Enter Last name to search: ");
					if((scanf("%s", userInput)) != 1){
						printf("Invalid Input\n");
					}else{
						inputValid = 0;
					}
					fflush(stdin);
				}
				search(myList.first, userInput);
			}
			//delete
	    }else if (option == 3) {printf("\nyou selected the delete function\n");
			if(myList.first == NULL){
				printf("No data in phone book!\nPlease use Add menu before using this menu!\n");
			}else{
				int inputValid = -1;
				char userInput[50];
				//check userInput
				while(inputValid == -1){
					printf("Please Enter Last name to search and delete: ");
					if(!isalpha(scanf("%s", userInput))){
						printf("Invalid Input\n");
					}else{
						inputValid = 0;
					}
					fflush(stdin);
				}
				delete(myList.first, userInput);
			}
		//showall
	    }else if (option == 4) {
			printf("-------------------------Clients---------------------------");
			showall(myList.first);
	    }else{
			save(myList);
			exit(0);
		
		}
		fflush(stdin);
	 	printf("\nselect 1 for inserting a new number to the phone book\nselect 2 to retrieve for a client's phone number\nselect 3 to delete an entry\nselect 4 for all the numbers in the phone book\n select any other key to exit\noption:  ");
	    scanf("%d", &option);
	}
}
