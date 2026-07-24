#ifndef SOBEL_BLOCK_H
#define SOBEL_BLOCK_H

/**
 * Aplica Sobel em um bloco horizontal da imagem.
 *
 * input:
 *  - bloco recebido pelo processo
 *  - contém linhas de halo
 *
 * output:
 *  - somente o resultado das linhas reais
 *
 * width:
 *  - largura da imagem
 *
 * height:
 *  - altura local sem contar halos
 */
void applySobelBlock(
    const unsigned char *input,
    unsigned char *output,
    int width,
    int height
);

#endif
