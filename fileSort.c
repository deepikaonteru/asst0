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
void printList(Node* root);
void destroy(Node* root);
void refresh(char* buffer, int count);
char isIntOrStringFile(Node* token);
int comparator( void* s1, void* s2);
int stringComparator( void* s1, void* s2);
int intComparator( void* s1, void* s2);
int insertionSort(void* toSort, int (*comparator)(void*, void*));
int quickSort( void* toSort, int (*comparator)(void*, void*)); 

Node* createNode(char* string){
	// allocate memory for a node with a defualt value
	Node* node = (Node*)(malloc(sizeof(Node)));
	node->next = NULL;	
	// allocate memory & point node->token at the string we want to copy into said Node
	node->token = strdup(string);
	return node;	
}

Node* insert(Node* root, char* string){	
	// if the root Node is NULL, add a new string to the front of the list, 
	// then return the updated root Node.
	if(root == NULL)
	{
		root = createNode(string);
		return root;
	}

	// add to beginning of list
		Node* newNode = createNode(string);
		newNode->next = root;
		return newNode;
}

Node* firstToken(Node* root){

	Node* tmp=root;
	while(tmp!=NULL) {
		if(tmp->token[0]=='\0') {
			tmp=tmp->next;
		}
		else {
			// Useful for setting flags
			return tmp;
		}
	}
	return tmp;

}


char isIntOrStringFile(Node* token){

	char nFlag;

	if (token == NULL){
		// file of ,,,,, or empty file
		nFlag  =  'e';
		printf("did that\n");
	}

	else if (isdigit(token->token[0]) || token->token[0] == '-'){
		nFlag = 'i';
	}

	else if (isalpha(token->token[0])){
		nFlag = 'a';
	}
	return nFlag; 

}


int comparator(void* s1, void* s2) {
	Node* firstToken = (Node*)s1;
	Node* secondToken = (Node*)s2;

	//printf("%s\n", firstToken->token);
	int ret;

	if (flag == 'i'){
		//printf("ye\n");
		ret = intComparator(firstToken->token, secondToken->token);
	}

	else if (flag == 'a'){
		//printf("ye\n");
		ret	= stringComparator(firstToken->token, secondToken->token);
	}
	return ret;
}

int stringComparator(void* s1, void* s2) {
	char* firstToken = (char*) s1;
	char* secondToken = (char*) s2;

	if (firstToken == NULL){
		return -1;
	}
	if (secondToken == NULL){
		return 1;
	}

	//Setting positions to check
	int i=0;
	while(firstToken[i]==secondToken[i] && firstToken[i]!='\0') {
		i ++;
	}
		   
	if(firstToken[i] < secondToken[i]){
		return -1;
	}
	else if(firstToken[i] > secondToken[i]){
		return 1;
	}
		
	return 0;
	
}


int intComparator( void* s1, void* s2) {

	char* firstToken = (char*) s1;
	char* secondToken = (char*) s2;

	if (firstToken[0] == '\0'){
		return -1;
	}
	if (secondToken[0] == '\0'){
		return 1;
	}

	int val1 = atoi(s1);
	int val2 = atoi(s2);

	
	if (val1 < val2){
		return -1;
	}
	else if (val1 > val2){
		return 1;
	}
		
	return 0;
	
}

void printList(Node* root){
	
	// create a ptr, set to NULL by default
	Node* ptr = NULL;
	
	// loop through while ptr isn't at the end of the list
	for(ptr = root; ptr!=NULL; ptr = ptr->next){

		//print string ptr is referencing
		printf("%s\n", ptr->token);
	}
} 

void destroy(Node* root){
	// reference to root
	Node* ptr = root;

	// run until there are no more pointers
	while(ptr != NULL){
		
		// make temp pointer to everything past ptr
		Node* temp = ptr->next;
		
		// free the char* the current Node as well as the Node itself
		free(ptr->token);
		free(ptr);
		
		// move the ptr to the next element in the list
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


int insertionSort(void* toSort, int (*comparator)(void*, void*)) {
	//printList(toSort);
	Node* unsortedList = (Node*)toSort;
	//printList(unsortedList);
	Node* sortedList = NULL;
	Node* curr = unsortedList;

	while(curr != NULL) {

		Node* next = curr->next;
		Node* toInsert = curr;
		/*insertIntoSortedList(sortedList, curr, comparator);*/
 		if(sortedList == NULL) {

			toInsert->next = sortedList;
			sortedList = toInsert;
		
			//printf("kiki %s\n",*unsortedList);
			//printList(sortedList);

		}
		else if(comparator(sortedList, toInsert)==1 ||
		     comparator(sortedList, toInsert)==0)
		{
			//int tst=comparator(sortedList, toInsert);
			//printf("%d\n", tst);
			toInsert->next = sortedList;
			sortedList = toInsert;
			//printf("do you %s\n",*unsortedList);
			//printList(sortedList);
		}

		else {

			Node* sortedPtr = sortedList;
			while(sortedPtr->next != NULL && comparator(sortedPtr->next, toInsert)==-1) {				
				sortedPtr = sortedPtr->next;
			}
			toInsert->next = sortedPtr->next;
			sortedPtr->next = toInsert;
			//printf("love me %s\n",*unsortedList);
			//printList(sortedList);
		}
	/*Done inserting one into sorted list*/
		curr = next;
	}

	unsortedList = sortedList;
	printList(sortedList);
 
}



int quickSort( void* toSort, int (*comparator)(void*, void*) ) {
}

int main(int argc, char* argv[]) {

	//initialize fd
	int fd = open("Readme.txt", O_RDONLY);

	//initialize list
	Node* root=readFile(fd);
	//printList(root);

	// find first non-empty token in order to use it to determine if we are dealing with ints or chars
	Node* firstNonEmptyToken = firstToken(root);

	flag = isIntOrStringFile(firstNonEmptyToken);
	//printf("%s\n",firstNonEmptyToken->token);
	//printf("%c\n",flag);
	/*
	void* word1 = "banana";
	void* word2 = "apple";
	int test = stringComparator(word1,word2);
	printf("%d\n",test);
	*/
	/*
	void* int1 = "anirudh";
	void* int2 = "aditya";
	int test = stringComparator(int1,int2);
	printf("%d\n", test);
	*/



	//printf("%c\n",flag);
	printList(root);
	printf("endoforiglist\n");

	//int (*fnPtr)(void*, void*) = comparator;
	insertionSort(root, comparator);
	//printList(root);

	destroy(root);
	close(fd);

}

//read from a file and extract tokens
//code linked lists for sorting purposes
//insertion sort
//quicksort
//integer and string comparator (cast void* input inside functions)
//modify sort code to accept comparators