#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
  
int main(int argc, char *argv[]) 
{ 
	   // We allocate a buffer of 5 bytes which includes also the termination, NULL.
	   // The allocation should be done as 8 bytes which is two double words.
	   // For overflowing process we will need more than 8 bytes.
	   
	   // if the user provides more than 8 characters for the input,
	   // an access violation and fault segmentation
       char buffer_test_example[5]; 
	   // execution of the program
       if (argc < 2) 
       { 
              printf("Function strcpy() will not be executed...\n"); 
              printf("The syntax: %s <characters>\n", argv[0]); 
              exit(0); 
       }  
       
	   // Take the input from the user and copy it to the buffer.
	   // The process is done without verifying the bound 
       strcpy(buffer_test_example, argv[1]); 
       printf("The content of thebuffer -> %s\n", buffer_test_example); 
 
       printf("The function strcpy() is being executed...\n"); 
  
       return 0; 
} 