#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/* Node struct to store string tokens that will form a linked list*/
typedef struct Node{
	char* token; 
	struct Node* next;
} Node;

/* flag stores whether file is ints or chars*/
char flag;

Node* readFile(int fd);
Node* createNode(char* string);
Node* insert(Node* root, char* string);
Node* firstToken(Node* root);
char isIntOrStringFile(Node* token);
int comparator( void* s1, void* s2);
int stringComparator( void* s1, void* s2);
int intComparator( void* s1, void* s2);
void printList(Node* root);
void destroy(Node* root);
void refresh(char* buffer, int count);


Node* createNode(char* string){
	//allocate memory for a node with a defualt value
	//Node* node = (Node*)calloc(1, sizeof(Node));
	Node* node = (Node*)(malloc(sizeof(Node)));
	node->next = NULL;	
	//allocate memory & point node->token at the string we want to copy into said Node
	node->token = strdup(string);
	//node->token=string;
	return node;	
}

Node* insert(Node* root, char* string){	
	//if the root Node is NULL, add a new string to the front of the list, 
	//then return the updated root Node.
	if(root == NULL)
	{
		root = createNode(string);
		return root;
	}

	//add to beginning of list
		Node* newNode = createNode(string);
		newNode->next = root;
		return newNode;
}

Node* firstToken(Node* root){

	do {
		if(root!=NULL){
			return root;
		}
		root = root->next;
	} while(root != NULL && root->token != NULL);

}

char isIntOrStringFile(Node* token){

	int i=0;
	char flag;

	if (token == NULL){
		// file of ,,,,, or empty file
		flag  =  'e';
	}

	if (isdigit(token->token[i]) || token->token[i] == '-'){
		flag = 'i';
	}

	if (isalpha(token->token[i])){
		flag = 'a';
	}

	return flag; 

}

int comparator( void* s1, void* s2) {
	Node* firstToken = s1;
	Node* secondToken = s2;

	int ret;

	if (flag == 'i'){
		ret = intComparator(firstToken->token, secondToken->token);
	}

	if (flag == 's'){
		ret	= stringComparator(firstToken->token, secondToken->token);
	}
}

int stringComparator(void* s1, void* s2) {
	int i,ret;
	char* firstToken = (char*) s1;
	char* secondToken = (char*) s2;

	if (firstToken == NULL){
		return -1;
	}
	if (secondToken == NULL){
		return 1;
	}

	for(i = 0; firstToken[i] == secondToken[i] && firstToken[i] == '\0'; i++){
	}
		   
	if(firstToken[i] < secondToken[i]){
		ret = -1;
	}
	else if(firstToken[i] > secondToken[i]){
		ret = 1;
	}
	else{
		//both are same
		ret = -1;
	}
	
	return ret;	
}


int intComparator( void* s1, void* s2) {
	int val1 = atoi(s1);
	int val2 = atoi(s2);
	int ret;

	if (val1 < val2){
		ret = -1;
	}
	else if (val1 > val2){
		ret = 1;
	}
	else{
		ret = -1;
	}
}

void printList(Node* root){
	
	//create a ptr, set to NULL by default
	Node* ptr = NULL;
	
	//loop through while ptr isn't at the end of the list
	for(ptr = root; ptr!=NULL; ptr = ptr->next){

		//print string ptr is referencing
		printf("%s\n", ptr->token);
	}
} 

void destroy(Node* root){
	//reference to root
	Node* ptr = root;

	//run until there are no more pointers
	while(ptr != NULL){
		
		//make temp pointer to everything past ptr
		Node* temp = ptr->next;
		
		//free the char* the current Node as well as the Node itself
		free(ptr->token);
		free(ptr);
		
		//move the ptr to the next element in the list
		ptr = temp;
	}
}

void refresh(char* buffer, int count){

	int i;
	for(i=0; i<count; i ++) {

		buffer[i]='\0';

	}

}

Node* readFile(int fd) {

	char buffer[200];
	int i;
	for(i=0; i<200; i ++) {

		buffer[i]='\0';

	}
	int bytesRead;
	int count=0;
	Node* root;

	do {

		char c=0;
		bytesRead = read(fd, &c, sizeof(char));
		//printf("%d\n", bytesRead);
		//printf("%c\n", c);
		//CHECKS
		if(c == ',' || bytesRead == 0) {

			/*Create Node HERE*/
			root = insert(root, buffer);
			//printf("%s\n", root->token);
			//printf("%s\n", buffer);
			refresh(buffer, count);
			count=0;
			

		}
		else if(isspace(c)) {

			continue;

		}
		else {

			buffer[count] = c;
			count ++;

		}
		

	} while(bytesRead > 0);

	return root;

}

/* function to sort a singly linked list using insertion sort */
int insertionSort( void* toSort, int (*comparator)(void*, void*) ) {
	//passing in head of linked list of the file 
	struct Node *sorted = NULL; 

	// traverse the given linked list and insert every node to sorted 
    struct Node* current = *toSort; 
    while (current != NULL) 
    { 
        // Store next for next iteration 
        struct Node* token = current->token; 
  
        // insert current in sorted linked list 
        sortedInsert(&sorted, current); 
  
        // Update current 
        current = current->next; 
    } 
  
    // Update head_ref to point to sorted linked list 
    *toSort = sorted; 

}
  
void sortedInsert(struct Node** head_ref, struct Node* new_node) { 
    struct Node* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head_ref; 
        while (current->next!=NULL && 
               current->next->data < new_node->data) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 


/*
int quickSort( void* toSort, int (*comparator)(void*, void*) ) {

}*/

int main(int argc, char* argv[]) {

	//initialize fd
	int fd = open("Readme.txt", O_RDONLY);

	//initialize list
	Node* root=readFile(fd);
	printList(root);

	//find first non-empty token in order to use it to determine if we are dealing with ints or chars
	Node* firstNonEmptyToken = firstToken(root);

	flag = isIntOrStringFile(firstNonEmptyToken);
	printf("%s\n",firstNonEmptyToken->token);
	printf("%c\n",flag);

	char* word1 = "apple";
	char* word2 = "apple";
	int test = stringComparator(word1,word2);
	printf("%d\n",test);

	close(fd);

}

//read from a file and extract tokens
//code linked lists for sorting purposes
//insertion sort
//quicksort
//integer and string comparator (cast void* input inside functions)
//modify sort code to accept comparators
