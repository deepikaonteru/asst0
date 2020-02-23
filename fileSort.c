#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//hello


int main(int argc, char ** argv){

	// ./fileSort -i ./somefile
	
	int fd  = open (argv[2], O_RDONLY|OCREAT, 0);
	
	// using lseek to get file size, gets cursor to end of file
	//int size = lseek(fd, 0, SEEK_END);
	
	//lseek(fd, -size, SEEK_END);

	// holding chars in an array buffer
	//char* buffer = (char*)malloc(sizeof(char)* size+1);
	//buffer[size] = '\0';

	if (fd  < 0) {
		printf("error,this is an empty file");
		return -1;
	}
	
	//tracking how much of the file read func has read in status	
	/* int status = 1;
	int written = 0;

	while (status > 0 && written < size) {
		//making sure read does not stop in the middle
		status = read(fd, buffer + written, size - written);
		written += status;
	}
	*/

	if (fd == -1)
	{
		printf("file won't open\n");
		return -1;
	}

	//tokenize the words
	

	printf("file is opened/n");

	//close file
	close(fd);
}

void readFile (int fd) {
    char buffer[10];
    int bytes_read;
    int k = 0;
    do {
        char t = 0;
        bytes_read = read(fd, &t, sizeof(char)); 
        buffer[k++] = t;    
        printf("%c", t);
        if(t == '\n' && t == '\0') {
            printf("%d", atoi(buffer));
            for(int i=0; i<10; i++) 
                buffer[i]='\0';
            k = 0;
        }
    }
    while (bytes_read < 0); 
}

//read from a file and extract tokens
//code linked lists for sorting purposes
//insertion sort
//quicksort
//integer and string comparator (cast void* input insidee functions)
//modify sort code to accept comparators

