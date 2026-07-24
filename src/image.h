#ifndef IMAGE_H
#define IMAGE_H

typedef struct
{
    int width;
    int height;
    int maxValue;
    unsigned char *pixels;
} Image;

/**
 * Carrega uma imagem PGM (P5).
 *
 * Retorna um ponteiro para Image ou NULL em caso de erro.
 */
Image *loadPGM(const char *filename);

/**
 * Salva uma imagem PGM (P5).
 *
 * Retorna 1 em caso de sucesso ou 0 em caso de erro.
 */
int savePGM(const char *filename, const Image *img);

/**
 * Libera toda a memória da imagem.
 */
void freeImage(Image *img);

#endif

