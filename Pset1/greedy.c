// greedy algorithm 

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float cash;
    int coins = 0;
    do
    {
        printf("O hai! How much change is owed?\n");
        cash = GetFloat();
    // improves cash input by multiplying by 100    
        cash = round(cash * 100);
        float quator = 25, dime = 10, nickel = 5, penny = 1;
    // counts quaotor greedily
        while(cash >= quator)
        {
            coins++;
            cash = cash - quator;
          
        }
        
    // counts dime greedily 
        while(cash >= dime)
        { 
            coins++;
            cash = cash - dime;
      
           
        }
        
        
     // counts nickel greedily   
        while(cash >= nickel)
        { 
            coins++;
            cash = cash - nickel;
            
      
        }
        
     // counts penny greedily  
        while(cash >= penny)
        {
            coins++;
            cash = cash - penny;

        }
   
   // prints number of coins
        printf("%d\n",coins);
  

    
    
}while(!(cash >= 0.00));

}
