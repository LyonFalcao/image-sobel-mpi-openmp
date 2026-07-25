#ifndef SOBEL_BLOCK_H
#define SOBEL_BLOCK_H

void applySobelBlock(
    const unsigned char *input,
    unsigned char *output,
    int width,
    int height
);

#endif
