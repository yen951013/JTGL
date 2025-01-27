#ifndef _JTGL_H
#define _JTGL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

uint32_t *JTGL_newPixelArray(size_t size) {
    uint32_t *pixels = malloc(size * sizeof(uint32_t));
    if (pixels == NULL) {
        printf("Error: JTGL_newPixelArray: Could not allocate memory\n");
        return NULL;
    }
    return pixels;
}

void JTGL_fillColor(uint32_t *pixels, size_t width, size_t height, uint32_t color) {
    for (size_t i = 0; i < width * height; i++) {
        pixels[i] = color;
    }
}

void JTGL_fillRect(uint32_t *pixels, size_t width, size_t height,
                   size_t x0, size_t y0, size_t w, size_t h, uint32_t color) {
    for (size_t i = 0; i < h; i++) {
        size_t y = y0 + i;
        if (y < 0 || y >= height)
            continue;
        for (size_t j = 0; j < w; j++) {
            size_t x = x0 + j;
            if (x < 0 || x >= width)
                continue;
            pixels[y * width + x] = color;
        }
    }
}

bool JTGL_exportToPpm(uint32_t *pixels, size_t width, size_t height, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error: Could not open file for writing\n");
        return false;
    }

    if (fprintf(fp, "P6\n%zu %zu\n255\n", width, height) < 0) {
        printf("Error: Could not write to file\n");
        fclose(fp);
        return false;
    }
    
    for (size_t i = 0; i < width * height; i++) {
        uint8_t bytes[3] = {
            (pixels[i] >> 8 * 0) & 0xFF,
            (pixels[i] >> 8 * 1) & 0xFF,
            (pixels[i] >> 8 * 2) & 0xFF
        };
        if (fwrite(&bytes, sizeof(bytes), 1, fp) != 1) {
            printf("Error: Could not write to file\n");
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

#endif  // _JTGL_H