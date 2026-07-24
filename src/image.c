#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void skipComments(FILE *fp)
{
    int c;

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '#')
        {
            while ((c = fgetc(fp)) != '\n' && c != EOF)
                ;
        }
        else if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
        {
            continue;
        }
        else
        {
            ungetc(c, fp);
            return;
        }
    }
}

Image *loadPGM(const char *filename)
{
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        return NULL;
    }

    char magic[3];

    if (fscanf(fp, "%2s", magic) != 1)
    {
        fclose(fp);
        return NULL;
    }

    if (strcmp(magic, "P5") != 0)
    {
        fclose(fp);
        return NULL;
    }

    Image *img = malloc(sizeof(Image));

    if (img == NULL)
    {
        fclose(fp);
        return NULL;
    }

    skipComments(fp);
    if (fscanf(fp, "%d", &img->width) != 1)
    {
        free(img);
        fclose(fp);
        return NULL;
    }

    skipComments(fp);
    if (fscanf(fp, "%d", &img->height) != 1)
    {
        free(img);
        fclose(fp);
        return NULL;
    }

    skipComments(fp);
    if (fscanf(fp, "%d", &img->maxValue) != 1)
    {
        free(img);
        fclose(fp);
        return NULL;
    }
    
    fgetc(fp);

    size_t imageSize = (size_t)img->width * img->height;

    img->pixels = malloc(imageSize);

    if (img->pixels == NULL)
    {
        free(img);
        fclose(fp);
        return NULL;
    }

    if (fread(img->pixels, 1, imageSize, fp) != imageSize)
    {
        free(img->pixels);
        free(img);
        fclose(fp);
        return NULL;
    }

    fclose(fp);

    return img;
}

int savePGM(const char *filename, const Image *img)
{
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        return 0;
    }

    fprintf(fp,
            "P5\n%d %d\n%d\n",
            img->width,
            img->height,
            img->maxValue);

    size_t imageSize = (size_t)img->width * img->height;

    if (fwrite(img->pixels, 1, imageSize, fp) != imageSize)
    {
        fclose(fp);
        return 0;
    }

    fclose(fp);

    return 1;
}

void freeImage(Image *img)
{
    if (img == NULL)
    {
        return;
    }

    free(img->pixels);
    free(img);
}
