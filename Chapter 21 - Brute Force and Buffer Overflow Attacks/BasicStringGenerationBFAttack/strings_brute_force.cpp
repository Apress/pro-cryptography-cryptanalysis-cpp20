#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
// We are using a linked list data structure. 
// The reasong is to avoid some of the restrictions 
//      based on the generation of the string length.
// Our list has to be converted to string in 
//      such way that it can be used. The current conversion
//      might be a little slower comparing with other methods
//      due to the fact that the conversion is happening with 
//      each cycle.

// Another solution consists in implementing a solution based
//      on the generation of the allocation for the string with 
//      a fixed size equal with 20 characters (which is more than
//      enough.

// the structure definition for holding the characters (strings)
typedef struct charactersList charlist_t;
struct charactersList
{
	// the character
    unsigned char character;
	// the next character
    charlist_t* nextCharacter;
};
 
// The method will return a new initialized charlist_t element.
// The element returned is charlist_t
charlist_t* new_characterList_element()
{
    charlist_t* elementFromTheList;

	if ((elementFromTheList = (charlist_t*) malloc(sizeof(charlist_t))) != 0)
    {
        elementFromTheList->character = 0;
        elementFromTheList->nextCharacter = NULL;
    }
    else
    {
        perror("The allocation using malloc() has failed.");
    }

    return elementFromTheList;
}

 // allocation free memory by the characters list
 // listOfCharacters - represents a pointer for the first element within the list
void freeAllocation_CharactersList(charlist_t* listOfCharacters)		
{
    charlist_t* currentCharacter = listOfCharacters;
    charlist_t* nextCharacter;

    while (currentCharacter != NULL)
    {
        nextCharacter = currentCharacter->nextCharacter;
        free(currentCharacter);
        currentCharacter = nextCharacter;
    }
}

 
// the function display the current list of characters
// the function will iterate through the whole list and it will print all the characters
void showCharactersList(charlist_t* list)	
{
    charlist_t* nextCharacter = list;
    while (nextCharacter != NULL)
    {
        printf("%d ", nextCharacter->character);
        nextCharacter = nextCharacter->nextCharacter;
    }
    printf("\n");
}
 
// the function will return the next sequence of characters.
// the characters are treated as numbers 0-255
// the function proceeds by incrementation of the character from the first position
void nextCharactersSequence(charlist_t* listOfCharacters)
{
    listOfCharacters->character++;
    if (listOfCharacters->character == 0)
    {
        if (listOfCharacters->nextCharacter == NULL)
        {
            listOfCharacters->nextCharacter = new_characterList_element();
        }
        else
        {
            nextCharactersSequence(listOfCharacters->nextCharacter);
        }
    }
}

int main()
{
    charlist_t* sequenceOfCharacters;
    sequenceOfCharacters = new_characterList_element();
	
	// this while will work for all possibles combinations
	// this has to be stopped manually
    while (1)
    {
        nextCharactersSequence(sequenceOfCharacters);
        showCharactersList(sequenceOfCharacters);
    }

    freeAllocation_CharactersList(sequenceOfCharacters);
}