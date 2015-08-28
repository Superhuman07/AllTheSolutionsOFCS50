// Program to print mario staircase

#include <stdio.h>
#include <cs50.h>

int main(void)
{  
    
    int height, i, j, k;
    do
    {
    // gets height value
        printf("Height: ");
        height = GetInt(); 
    
    // checks height values
        if (height <= 23 && height > 0)
        {
    
    // increments height
            for ( i = 0 ; i < height; i++)
            {
    // adds space character
                for ( j = height - i - 1; j > 0 ; j--)
                {   
                    printf("%c",32);
                }
    // adds appropriate #     
                for ( k = 0 ; k < i + 2 ; k++)   
                {   
                    printf("#");
                }
    // adds next line     
                printf("\n");
            }
    
    }
    
    }
    // checks height values
    while(!(height >= 0 && height <= 23));
}
