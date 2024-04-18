#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Author: Nicholas Bonilla
    Purpose: Count occurances of a word using trie
    Date: 4/18/2024
    */

// Trie structure
struct Trie
{	
    int isWord;
	int count;
    struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
	//Allocating memory
	struct Trie* tree = malloc(sizeof(struct Trie));

	//Setting all pointers to null
	for(int i = 0; i < 26; i++)
	{
		tree->children[i] = NULL;
	}

	tree->isWord = 0;
	int count = 0;

	//Returning pointer
	return tree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    //Making temp pointer
	struct Trie *temp = pTrie;

	//Getting strlen and index
	int len = strlen(*word);
	int index;
	
	//Filling in vals
	for(int i = 0; i < len; i++)
	{
		if(i == len)
		{
			temp->isWord = 1;
			temp->count++;
			break;
		}

		//Checking if trie index is initialized
		index = word[i] - 'a';
		if(pTrie->children[index] == NULL)
		{
			pTrie->children[index] = createTrie();
		}

		//Moving down trie
		insert(pTrie->children[index], word[i+1]);

	}
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    //Looping through all chars
    for(int i = 0; i < 26; i++)
    {
        //Checking if child trie is found
        if(pTrie->children[i] != NULL)
        {
            //If found, call recursion to free child trie memory
            deallocateTrie(pTrie->children[i]);
        }
    }

    //Freeing Memory
    free(pTrie);
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	//Creating File Pointer
	FILE* ptr = fopen(filename, "r");

	//Making counter variable
	int count;
	fscanf(ptr, "%d", &count);
	char word[100];
	//Reading and counting words
	for(int i = 0; i < count; i++)
	{
		fscanf(ptr, "%s", word);
		pInWords[i]=word;
		printf("%s",pInWords[i]);
	}

	//Returning count
	return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}