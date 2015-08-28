#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
#define BLOCKSIZE 512

int main (void)
{
    // opening the given memory card
	FILE* card = fopen("card.raw", "r");
	
	// if card is NULL don't proceed
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // opening the output file as NULL
    FILE *outcard = NULL;
    
    int jpgnum = 0; 
    while (1)
    {
        // create an array called block that's the size of BLOCKSIZE
        BYTE block[BLOCKSIZE] = {};
        
        // iterate over each byte in each block until you reach the end of the file
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            // if you reach the end of file, close the file
            if (feof(card))
            {
                fclose(card);
                
                // close previously opened output file pointer if necessary
                if (outcard != NULL)
                    fclose(outcard);
                    
                return 0;
            }
            
            // read one byte at a time
            fread(&block[i], sizeof (BYTE), 1, card);
        }
        
        // if block's first 4 bytes match those of a jpg (start of new jpg)      
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // close previously opened output file pointer if necessary
            if (outcard != NULL)
            {
                fclose(outcard);
            }
            
            // create a constant char array for filename
            char filename[4];
            
            // name file using ###.jpg format
            sprintf(filename, "%03d.jpg", jpgnum);
            jpgnum++; 
            
            // open the output file pointer and make sure it's not NULL
            if ((outcard = fopen(filename, "w")) == NULL)
            {
                printf("Could not recover image.\n");
                return 1;
            }
 
            // write the block containing jpg to the outcard
            fwrite(&block[0], BLOCKSIZE * sizeof (BYTE), 1, outcard);
        }
        
        // if outcard has been opened, write the block to the outcard
        else if (outcard != NULL) 
        {
            fwrite(&block[0], BLOCKSIZE * sizeof (BYTE), 1, outcard);
        }
    }
 
    // close memory card
    fclose(card);
    return 0;
}
