#include "JTGL.c"
#include <stdio.h>

const size_t HEIGHT = 400;
const size_t WIDTH = 600;

int main() {
    uint32_t *pixels = JTGL_newPixelArray(HEIGHT * WIDTH);
    if (pixels == NULL) {
        printf("Error: main: Could not allocate memory for pixels\n");
        return -1;
    }
    JTGL_fillColor(pixels, WIDTH, HEIGHT, 0xFF121212);
    JTGL_fillRect(pixels, WIDTH, HEIGHT, WIDTH/2 - 150/2, HEIGHT/2 - 100/2, 150, 100, 0xFF1212FF);

    if (!JTGL_exportToPpm(pixels, WIDTH, HEIGHT, "output.ppm")) {
        printf("Error: main: Could not export pixels to PPM\n");
        return -1;
    }

    return 0;
}