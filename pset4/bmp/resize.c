/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4 && (atoi(argv[1]) < 0 && atoi(argv[1]) > 100))
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // save infile dimensions
                    LONG inWidth = bi.biWidth;
                    LONG inHeight = bi.biHeight;

                    // recalc new image width & height
                    bi.biWidth *= factor;
                    bi.biHeight *= factor;

                    // determine padding for infile/outfile scanlines
                    int inpad = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;
                    int outpad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

                    // recalc image size with new width, height, and any padding
                    bi.biSizeImage = ((bi.biWidth * 3) + outpad) 
                        * abs(bi.biHeight);

                    // recalc bfSize to match new resized image
                    bf.bfSize = 
                        sizeof(BITMAPFILEHEADER) + 
                        sizeof(BITMAPINFOHEADER) + 
                        bi.biSizeImage;
    
      // determine padding for scanlines
    //int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((bi.biWidth * 3) + outpad) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  
    // iterate over infile's scanlines
    for (int i = 0, lines = abs(inHeight); i < lines; i++)
                    {
                        // save the file position; i.e. beginning of line
                        long pos = ftell(inptr);

                        // repeat scanline writes for factor
                        for (int j = 0; j < factor; j++)
                        {
                            // restore the position to beginning of same line
                            fseek(inptr, pos, SEEK_SET);

                            // iterate over pixels in scanline
                            for (int pixel = 0; pixel < inWidth; pixel++)
                            {
                                // temporary storage
                                RGBTRIPLE triple;

                                // read RGB triple from infile
                                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                                
                                // repeat write of RGB triple for factor
                                for (int pxf = 0; pxf < factor; pxf++)
                                {
                                    fwrite(&triple,sizeof(RGBTRIPLE),1,outptr);
                                }
                            }
        // skip over padding, if any
        fseek(inptr, inpad, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < outpad; k++)
        {
            fputc(0x00, outptr);
        }
    }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
