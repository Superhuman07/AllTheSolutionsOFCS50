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
    if (argc != 2)
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;
    }
    else if (argv[1])
    {
        int length = strlen(argv[1]);
        for (int i = 0; i < length; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Keyword must only contain letters A-Z and a-z\n");
                return 1;
            }
        }
    }

    string string1 = GetString();
    int member = 0;
    int keyindex = 0;
    string key = argv[1];     
    for (int i = 0 ; i < strlen(string1); i++)
    { 
        /* crypting on basis of the letters of keyword and 
           message
        */
        if (isalpha(string1[i]))
        {
            keyindex = member % strlen(key);
            if (islower(string1[i]))
            {
                if (islower(key[keyindex]))
                {
                    int crypted = ((string1[i] - 97 + key[keyindex] - 97) % 26) + 97;
                    printf("%c", crypted);
                }
                else
                {
                    int crypted = ((string1[i] - 97 + key[keyindex] - 65) % 26) + 97;
                    printf("%c", crypted);
                }
            }
            if (isupper(string1[i]))
            {
                if (islower(key[keyindex]))
                {
                    int crypted2= ((string1[i] - 65 + key[keyindex] - 97) % 26) + 65;
                    printf("%c", crypted2);
                }
                else
                {
                    int crypted2 = ((string1[i] - 65 + key[keyindex] - 65) % 26) + 65;
                    printf("%c", crypted2);
                }
            }
            // increasing key to length of the string1
            member++;
        }
        else
        {
            printf("%c", string1[i]);
        }
    }
    printf("\n");
}
