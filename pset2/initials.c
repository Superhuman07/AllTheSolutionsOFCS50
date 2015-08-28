/*
Program to print initial letters of a given user name i.e.
name intials in uppercase
*/

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    for(int i = 0, n = strlen(name); i < n; i++)
    {  
    // prints out first intial letter in uppercase
        if (i == 0)
        {
            printf("%c",toupper(name[i]));
        }
    // prints out intial letter in uppercase after a space char    
        if (name[i] == 32)
        {
            printf("%c",toupper(name[i + 1])); 
        }  
           
    } 
    printf("\n"); 
}
