/*
Program to ceasar crypt the given letters

*/

#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string sentence;
    if (argc != 2)
    {
        printf("Usage: ./caesar <key><Words>\n");
        return 1;
    }   
    string k = argv[1];
    int key = atoi(k);
    sentence = GetString();
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {   
    // converts to cyper by adding and subtracting ascii values
        if (islower(sentence[i]))
        {
            printf("%c",(((sentence[i] - 97 + key) % 26) + 97));
        }    
        else if (isupper(sentence[i]))
        {
            printf("%c",(((sentence[i] - 65 + key) % 26) + 65));
        }
        else
            printf("%c",sentence[i]);
        }
    printf("\n");
 
    return 0;
    
}
