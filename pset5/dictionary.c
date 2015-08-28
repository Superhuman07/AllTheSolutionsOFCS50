/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// size of the hash table
#define HASHTABLE_SIZE 3500
// word counts of the dictionary words
int word_count = 0;

/**
 * Creates a linked list.
 */
typedef struct node
{
	char* word;
	struct node* next;
}
node;
// creating a hash table of linked lists
node* hashTable[HASHTABLE_SIZE];

/**
 * Returns the hash value of the word i.e. hash function
 */
int hash(const char* word)
{
    int wordLen = 0;
    wordLen = strlen(word);
    int hashSum = 0;
    for(int i = 0; i < wordLen; i++)
    {
    	hashSum += word[i];
    }
    return hashSum%HASHTABLE_SIZE;
}
	
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char Temp_word[LENGTH+1];
    int lowerLetter;
    
    // converting all uppercase letters to lowercase
    for(int i = 0; i < strlen(word); i++)
    {
    	lowerLetter = tolower(word[i]);
    	Temp_word[i] = (char)lowerLetter;
    }
    // terminate this word
    Temp_word[strlen(word)] = '\0';
    
    int hashValue = hash(Temp_word);
    // the temporary list for checking
    node* tempList = hashTable[hashValue];
    // if the temporary list is empty the word return false because it must be misspelled
    if(tempList == NULL)
    {
    	return false;
    }
    
    while(tempList != NULL)
    {
    	if(!strcmp(tempList->word, Temp_word))
    	{
    		return true;
    	}
    	tempList = tempList->next;
    }
    return false;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false
 */
bool load(const char* dictionary)
{
   FILE* file = fopen(dictionary, "r");;
   int hashValue = 0 ;
   char dictWord[LENGTH+1];
   
   // if we dont have the permission to open return false
   if(file == NULL)
   {
   	return false;
   }
   
   
   while(fscanf(file,"%s\n", dictWord) != EOF)
   {
	   	// create new node size of node
	   	node* newList = malloc(sizeof(node));
	   	// +1 for '\0'
	   	newList->word = malloc(strlen(dictWord)+1);
	   	// copy the new word into the linked list 
	   	strcpy(newList->word,dictWord);
	  
	   	hashValue = hash(dictWord);
	   	
	   	word_count++;
	   	
	   	// sets the node in the hashtable to the new node, if there are other 
	   	// nodes then the new list is made the head   	
	   	if(hashTable[hashValue] == NULL)
	   	{
	   		hashTable[hashValue] = newList;
	   		newList->next = NULL;
	   	}else
	   	{
	   		newList->next = hashTable[hashValue];
	   		hashTable[hashValue] = newList;
	   	}   	
   	
   }
    fclose(file);
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	node* temp_list = NULL;
	node* temp_list2 = NULL;
	
	// iterates through the hashtable
	for(int i = 0; i < HASHTABLE_SIZE;i++)
	{
		temp_list = hashTable[i];
		
		if(temp_list && !temp_list->next)
		{
			free(temp_list->word);
			free(temp_list);
		}
		else
		{
			// freeing them one at a time
			while(temp_list)
			{
				temp_list2 = temp_list->next;
				free(temp_list->word);
				free(temp_list);
				temp_list = temp_list2;
			}
		}
		hashTable[i] = NULL;
	}
	return true;
}
