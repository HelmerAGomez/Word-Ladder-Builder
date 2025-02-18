
/*
Helmer Gomez            10/6/2024
CS 211                  FALL2024
zyBooks, IDE:CR2, language: C, macOs

Bit Big Bug Tug - Word Ladder Builder

This program will create the word ladder game where the goal is to start with a starter and asking the user to change one letter at a time to 
match the final world creating a world ladder that conncet the two words. This programs uses commands lines or user inputs
to get the length of the words in the word ladder and also the starter word and final word. The user will enter words that change by one
letter into the word ladder making sure the words are valid the game ends when the final word is reached.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// function that will be counting the number of differences between the words
// returns an int and the paramters are two c-string arrays
int strCmpCnt(char* word1, char* word2) {
    char* word1Itr = word1; // iterators for the two char arrays
    char* word2Itr = word2;
    int differenceCount = strlen(word2) - strlen(word1); // find the length difference if there is any and make it the base for the differences
    if(strlen(word2) <  strlen(word1)) { // if one char array is shorter than the other the one shortest will be iterated through for the indivual char diffs
        word1Itr = word2;   
        word2Itr = word1;
        differenceCount = strlen(word1) - strlen(word2); // switch the order so there is no negative values
    }
    while((*word1Itr) != '\0') {  // iterating through the shortest char array and finding any char differences and increasing the count by one 
        if((*word1Itr) != (*word2Itr)) {
            differenceCount++;
        }
        word1Itr++;
        word2Itr++;
    }
    return differenceCount; // returns the int differences
}

// fucntion that will return the index at where the first difference in the word is
// returns a int with the parameters being two c-strings
int strCmpInd(char* word1, char* word2) {
    char* word1Itr = word1; // iterators for the two char arrays
    char* word2Itr = word2;
    int differenceIndx = 0; // difference initialized
    if(strlen(word1) < strlen(word2)) { // if the first word is shorter than the seconds the word that will be iterated will be the second word
        word1Itr = word2;
        word2Itr = word1;
    }
    while((*word1Itr) != '\0') { // the shorter word will be iterated char by char and returns the first instace of a difference
        if((*word1Itr) != (*word2Itr)) {
            return differenceIndx;
        }
        differenceIndx++;
        word1Itr++;
        word2Itr++;
    }
    return -1; // if there is no difference it will return -1
}

// function will be adding c-strings to an array of c-strings allocating neccessay memory for each word as well as for the added word if needed
// void function parameters are the char** word array as pass by pointer and numOfWords pass by pointer as well as maxWords newWords is the char array 
void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
    if((*pNumWords) == (*pMaxWords)) {  // if the capacity is reached new memory must be allocated to increase the stored words in the array
        char** newPWords = (char**)malloc(sizeof(char*) * ((*pMaxWords) * 2)); // doubleing the capicty in the array
        for(size_t i = 0; i < (*pNumWords); i++) { // copying all the old elements to the new array
            newPWords[i] = (*pWords)[i];
        }
        free(*pWords); // free old array
        (*pWords) = newPWords; // assigning the new array with increased size to the old array 
        (*pMaxWords) = (*pMaxWords) * 2; // updating the capacity 
    }
    (*pWords)[(*pNumWords)] = (char*)malloc(sizeof(char) * (strlen(newWord) + 1)); // allocating the memory neccessary to store the new word c-string
    strcpy((*pWords)[(*pNumWords)], newWord); // adding the new word to the allocated space
    (*pNumWords)++; // updatingn the new amount of words in the array
}

// function will return the index of the word that matches the words we are trying to find
// returns an int and the paramters are the word array, copy of the num of words in the array, and the c-string word we are trying to find
int linSearchForWord(char** words, int numWords, char* findWord) { 
    for(int i = 0; i < numWords; i++) { // iterates through the array of words and will return the index if there is a match 
        if (strcmp(words[i], findWord) == 0) {
            return i;
        }
    }

    return -99; // returns -99 if the word was not in the word array
}

// function will check if the word being added is valid in length, is in dict, and has only one change and return false if it fails these reqs
// returns a boolean and the paramteres are the word array, the copy of num of words, copy of wordlength, the array of words in the ladder, copy of the height of ladder, and the c-string to validate 
bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {
    // if the word is DONE then the fucntion will return true
    if (strcmp(aWord, "DONE") == 0) {
        printf("Stopping with an incomplete word ladder...\n");
        return true;
    }
    // if the word is not of the req length the funtion will return false
    if(strlen(aWord) != wordLen) {
        printf("Entered word does NOT have the correct length. Try again...\n");
        return false;
    }
    // if the word is not in the dictionray it will return false
    if(linSearchForWord(words,numWords,aWord) == -99) {
        printf("Entered word NOT in dictionary. Try again...\n");
        return false;
    }
    // if the word is not changed by one letter it will return false
    if((strCmpCnt(ladder[ladderHeight-1], aWord)) != 1) {
        printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
        return false;
    }
    // if there is no error it will return true that the word meets all the reqs
    printf( "Entered word is valid and will be added to the word ladder.\n");
    return true; // modify this
}

// function will return true or false if the last word matches the final word
// returns a boolean and the parameters are the ladder word array, copy of the height, the c-string of the final word
bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
    // if the last word in the ladder is the same as the final word it will return true
    if(strcmp(ladderWords[height-1], finalWord) == 0) {
        return true;
    }
    return false; // if the last word is not the same it will return false
}

// function will print the incompleted word ladder
// fucntion is a void function the parameters are the word ladder array and the copy of the height of the ladder array
void displayIncompleteLadder(char** ladderWords, int height) {
    printf("  ...\n");
    printf("  ...\n");
    printf("  ...\n");
    // reverse print the ladder word array
    for(size_t i = 0; i < height; i++) {
        printf("  %s\n", ladderWords[(height -1) - i]);
    }

}

// fucntion will print the completed word ladder with each change being noted
// void function has the parameters of the word ladder array and a copy of the height of the word ladder
void displayCompleteLadder(char** ladderWords, int height) {
    // for loop that will print the entire array 
    for(int i = 0; i < height - 1; i++) {
        printf("  %s\n", ladderWords[(height -1) - i]);
        printf("  ");
        // for loop that will print spaces for the words unchange and print '^' where the word changes
        for(int j = 0; j < strlen(ladderWords[(height -1) - (i+1)]); j++) {
            if(j == strCmpInd(ladderWords[(height -1) - (i+1)], ladderWords[(height -1) - i]) ){
                printf("^");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    // prints the first word in the ladder
    printf("  %s\n", ladderWords[0]);
}


int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 
    // command line arguments that will set variables 
    for(size_t i = 1; i < argc - 1; i++) {\
        // if the right prefix is found we look through the next item to know what needs to be set
        if(argv[i][0] == '-') {
            if(argv[i][1] == 'n') { // will set the wordlength
                if(atoi(argv[i+1]) > 1 && atoi(argv[i+1]) < 21) {
                    wordLen = atoi(argv[i+1]); // the use of atoi to conver chars array to a int
                }
            }
            if(argv[i][1] == 'm') { // will set the maxLadder capacity
                if(atoi(argv[i+1]) > 1) {
                    maxLadder = atoi(argv[i+1]);
                }
            }
            if(argv[i][1] == 'd') { // will set the dict to the file that exits
                FILE* tempDictFile = fopen(argv[i+1], "r"); // temporarly opens the file 
                if(tempDictFile != NULL) { // if the file exist then the name will be set to dict
                    strcpy(dict, argv[i+1]);
                }
                fclose(tempDictFile);
            }
            if(argv[i][1] == 's') { // assigns the starword
                strcpy(startWord, argv[i+1]);
            }
            if(argv[i][1] == 'f') { // assings the final word
                strcpy(finalWord, argv[i+1]);
            }                
        }
    }

    printf("Interactively (re)setting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        numInputs = scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }
    
    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen] 

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4

    char** words = (char**)malloc(maxWords*sizeof(char*));
    // we open the file as a read only
    fileTry = fopen(dict,"r");
    char currWord[50]; // declare currWord which will store the words form the file
    while (!feof(fileTry)) { // if we have not reached the end of file we will continue on
      fscanf(fileTry, "%s", currWord); // assigns the c-string to currword
      if(strlen(currWord) == wordLen) { // if the word matches the req length it will be added to the word array
        appendWord(&words,&numWords,&maxWords,currWord);
      }
   }
   fclose(fileTry); // finaly closes the file
    

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");

    // a while loop that will execute if the ladderHeight is not equal to the maxLadder as well as if the word ladder is not complete and also if the user did not enter "DONE"
    // the while loop will continue to add words to the word ladder if any of the above condition are not met
    while ( (ladderHeight < maxLadder) && (strcmp(aWord, "DONE") != 0) && !(isLadderComplete(ladder, ladderHeight, finalWord)) )  {   // modify this line 
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");

    }
    

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
    
    
    // we will free all of the allocated memory in the heap starting with the c-strings allocated to the heap for the ladder and words arrays
    for(int i = 0; i < ladderHeight; i++) {
        free(ladder[i]);
    }
    for(int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    // finaly we can free the arrays of pointers for ladder and words
    free(ladder);
    free(words);

    return 0;
}