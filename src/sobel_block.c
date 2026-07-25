#include "sobel_block.h"

#include <stdlib.h>
#include <omp.h>


static int getPixel(
    const unsigned char *img,
    int x,
    int y,
    int width,
    int height
)
{

    if (x < 0 || x >= width ||
        y < 0 || y >= height)
    {
        return 0;
    }

    return img[y * width + x];
}



void applySobelBlock(
    const unsigned char *input,
    unsigned char *output,
    int width,
    int height
)
{

   
    #pragma omp parallel for
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
        
        int localY = y + 1;


            int gx =
                -getPixel(input, x-1, localY-1, width, height+2)
                +getPixel(input, x+1, localY-1, width, height+2)

                -2*getPixel(input, x-1, localY, width, height+2)
                +2*getPixel(input, x+1, localY, width, height+2)

                -getPixel(input, x-1, localY+1, width, height+2)
                +getPixel(input, x+1, localY+1, width, height+2);



            int gy =
                -getPixel(input, x-1, localY-1, width, height+2)
                -2*getPixel(input, x, localY-1, width, height+2)
                -getPixel(input, x+1, localY-1, width, height+2)

                +getPixel(input, x-1, localY+1, width, height+2)
                +2*getPixel(input, x, localY+1, width, height+2)
                +getPixel(input, x+1, localY+1, width, height+2);



            int magnitude = abs(gx) + abs(gy);


            if (magnitude > 255)
                magnitude = 255;


            output[y * width + x] =
                (unsigned char)magnitude;
        }
    }
}
