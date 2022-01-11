///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2020
//
// Author:           Lukas Wehrli
// Email:            lwehrli@wisc.edu
// CS Login:         wehrli
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {    
    printf("%s\n", "Enter magic square's size (odd integer >=3)");
    char userInput[100];
    fgets(userInput, 100, stdin);
    
    int userInt = atoi(userInput);
    	
    if(userInt >= 3){
	if(userInt % 2 == 1){
	    return userInt;
	}else{
	    printf("%s\n", "Size must be odd.");
	    exit(1);
	}
    }else{
	printf("%s\n", "Size must be >=3.");
	exit(1);
    } 	   
}
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rosw and columns
 */
MagicSquare *generateMagicSquare(int n) {
    MagicSquare *newSquare = malloc(sizeof(MagicSquare));
    newSquare->size = n;
    newSquare->magic_square = malloc(sizeof(int *) * n);

    if (newSquare->magic_square == NULL){
	printf("%s\n", "Error creating array.");
	exit(1);
    }

    for(int i = 0; i < n; i++){
	*(newSquare->magic_square + i) = malloc(sizeof(int) * n);

	if(*(newSquare->magic_square + i) == NULL){
	    printf("%s\n", "Error creating array.");
	    exit(1);
	}
    }

    int counter = 1;
    int exitLoop = 0;
    int i = 0;
    int j = (n /2);
    int contLoop = 1;

    while(contLoop == 1){
	while(contLoop == 1){
	    if (i != 0 && j != n - 1){
		// if we are not at the edge of the array
	       	if(*(*(newSquare->magic_square + i) + j) != 0){
		    // if there is a number up and to the right
		    
		    i = i + 2;
		    j = j - 1;
		    // go down in the array and put a number
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = i - 1;
		    j = j + 1;

	   	}else{
		    // the square up and to the right is free
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = i - 1;
		    j = j + 1;
	  	}
	    }else if(i == 0 && j != n - 1){
		// if we are at the top of the array
		if(*(*(newSquare->magic_square + i) + j) != 0){
		    // if the square to the top right is not free
		    i = i + 2;
		    j = j - 1;
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = i - 1;
		    j = j + 1;
		}else{
		    // if the square to the top right if free
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = n - 1;
		    j = j + 1;
		}
	    }else if(j == n - 1 && i != 0){
		// if we are at the far right of the array
		if(*(*(newSquare->magic_square + i) + j) != 0){
		    // the square to the top right is not free
		    i = i + 2;
		    j = j - 1;
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = i - 1;
		    j = j + 1;
		}else{
		    // the square to the top right is free
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    j = 0;
		    i = i - 1;
		}
	    }else{
		// we are at both the top and the far right of the array
		// i = 0 and j = n - 1
		if (*(*(newSquare->magic_square + i) + j) != 0){
		    // the very bottom left is not empty
		    i = 1;
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		}else{
		    // the bottom left is empty
		    *(*(newSquare->magic_square + i) + j) = counter;
		    counter = counter + 1;
		    i = i + 1;
		}
	    }
	    if (counter > (n * n)){
		exitLoop = 1;
		break;
	    }
	}
	if (exitLoop == 1){
	    break;
	}
    }

    return newSquare;
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL){
	printf("%s\n", "Can't open file for writing.");
	exit(1);
    }

    int size = magic_square->size;

    fprintf(fp,"%d\n", size);

    for(int i = 0; i < size; i ++){
	for(int j = 0; j < size; j++){
	    if( j == size - 1){
		// if it is the end of a row
		fprintf(fp, "%d\n", *(*(magic_square->magic_square + i) + j));
	    }else{
		// if it is not the end of a row
	    	fprintf(fp, "%d,", *(*(magic_square->magic_square + i) + j));
	    }
	}
    }

    if(fclose(fp) != 0){
	printf("%s\n", "Error while closing the file.");
	exit(1);
    }
    
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    if (argc != 2){
	printf("%s\n", "Usage: ./myMagicSquare <output_filename>");
	exit(1);
    }

    // TODO: Get magin square's size from user
    int userSize = getSize();
    
    // TODO: Generate the magic square
    MagicSquare *square = generateMagicSquare(userSize);
    // TODO: Output the magic square

    fileOutputMagicSquare(square, argv[1]);
    
    free(square);

    return 0;
} 


                                                         
//				myMagicSquare.c      

