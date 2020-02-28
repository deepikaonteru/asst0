#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// Node struct to store string tokens that will form a linked list
typedef struct Node{
	char* token; 
	struct Node* next;
} Node;

Node* create_node(char* string){
	//allocate memory for a node with a defualt value
	//Node* node = (Node*)calloc(1, sizeof(Node));
	Node* node = (Node*)(malloc(sizeof(Node)));
	node->next = NULL;	
	//allocate memory & point node->token at the string we want to copy into said Node
	node->token = strdup(string);
	//node->token=string;
	return node;	
}

/*
int inserionSort( void* toSort, int (*comparator)(void*, void*) ) {

}*/


Node* insert(Node* root, char* string){	
	//if the root Node is NULL, add a new string to the front of the list, 
	//then return the updated root Node.
	if(root == NULL)
	{
		root = create_node(string);
		return root;
	}

	//add to beginning of list
		Node* newNode = create_node(string);
		newNode->next = root;
		return newNode;
}
/*
int comparator( void* s1, void* s2) {

	
	/*
	int i=0,  ret;

	//CHECK if chars or nums to cast 
	if (isalpha(s1[i])) {
		(char*) s1;
		(char*) s2;
	}

	if (s1[i].isdigit()){
		// remember negative numbers '-'
		(int*) s1;
		(int*) s2;
	}
	
	//lowercase letters or numbers
	for(i=0; i< strlen(s1); i++){
		for(i=0; strlen(s2); i++){
			if (s1[i] < s2[i]){
				ret = -1;
				break;
			}
			else if (s1[i] > s2[i]){
				ret = 1;
				break;
			}
			else{
				continue;
			}
		}
		return ret;	
	}
	*/

void print_list(Node* root){
	
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

void refresh(char* buffer, int count) {

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

int main(int argc, char* argv[]) {

	//initialize fd
	int fd = open("Readme.txt", O_RDONLY);

	//Initialize list
	Node* root=readFile(fd);
	print_list(root);

}

//read from a file and extract tokens
//code linked lists for sorting purposes
//insertion sort
//quicksort
//integer and string comparator (cast void* input insidee functions)
//modify sort code to accept comparators

