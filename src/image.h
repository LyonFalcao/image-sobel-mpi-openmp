#ifndef IMAGE_H
#define IMAGE_H

typedef struct
{
    int width;
    int height;
    int maxValue;
    unsigned char *pixels;
} Image;

Image *loadPGM(const char *filename);

int savePGM(const char *filename, const Image *img);

void freeImage(Image *img);

#endif

