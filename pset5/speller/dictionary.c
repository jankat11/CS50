// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int size_of_dict;

// TODO: Choose number of buckets in hash table
const unsigned int N = 728;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    node *temp = NULL;



    for (temp = table[hash(word)]; temp != NULL; temp = temp->next)
    {

        if (strcasecmp(word, temp->word) == 0)
        {

            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (strlen(word) == 1)
    {
        return toupper(word[0])  - 'A';
    }
    else if (strlen(word) > 1 && isalpha(word[1]))
    {
        return ((toupper(word[0])  - 'A') + 1) * 26 + (toupper(word[1])  - 'A');
    }
    else if (strlen(word) > 1 && (int)word[1] == 39)
    {
        return 701 + toupper(word[0])  - 'A' + 1;
    }

    return 0;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return 1;
    }

    string dict;
    node *w = NULL;

    dict = malloc((LENGTH + 1) * sizeof(char));
    if (dict == NULL)
    {
        return 1;
    }

    int word_count = 0;
    while (fscanf(file, "%s", dict) != EOF)
    {

        w = malloc(sizeof(node));
        if (w == NULL)
        {
            return 1;
        }

        strcpy(w->word, dict);

        w->next = table[hash(dict)];
        table[hash(dict)] = w;

        word_count++;
    }
    printf("%i", word_count);
    free(dict);
    fclose(file);
    size_of_dict = word_count;
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_of_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
