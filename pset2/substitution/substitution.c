#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //if key does not exist claim it.
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check if key does not contain 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // check if exist non - alphabetic characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain 26 alphabetic characters\n");
            return 1;
        }
    }

    // check if exist duplicated characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j] && i != j)
            {
                printf("Key mustn't contain duplicate characters\n");
                return 1;
            }
        }
    }

    // ask for plain text
    char *plaintext = get_string("plaintext: ");

    //create a key array (each number represent new character in new order)
    char key[26];
    for (int i = 0; i < 26; i++)
    {
        key[i] = (argv[1][i]);
    }

    // copy whole string as named ciphertext
    char *ciphertext = malloc(sizeof(char) * strlen(plaintext));
    for (int i = 0; i < strlen(plaintext); i++)
    {
        ciphertext[i] = (plaintext[i]);
    }

    //change each character according given key
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        if (isalpha(ciphertext[i]) && islower(ciphertext[i]))
        {
            ciphertext[i] = tolower(key[(int)ciphertext[i] - 97]);
        }
        else if (isalpha(ciphertext[i]) && isupper(ciphertext[i]))
        {
            ciphertext[i] = toupper(key[(int)ciphertext[i] - 65]);
        }
    }
    //print crypted text
    printf("ciphertext: %s\n", ciphertext);
}