#include <stdio.h>
#include <stdlib.h>
#include "src/stb_image.h"
#include "src/stb_image_write.h"


int main(void) {
    int width, height, channels;
    
    // Load and set grayscale
    
    unsigned char *image = stbi_load("box.png", &width, &height, &channels, 1); // Note: 1 makes it grayscale (ie, 1 channel)
    
    if (!image){ printf("Failed load image"); return 1; }
    printf("Loaded image: %d,%d, channel: %d\n", width, height, channels);
    
    // Store pixel data in a 2D array

    // Used VLA's
    int (*pixel_data)[width][height]; // creates 2D array for pixel data
    malloc(sizeof *pixel_data); // Allocate memory for pixel_data

    for (int y = 0; y < height; y++){ // loops through every pixel 1D is copied to 2D
        for (int x = 0; x < width; x++){
            (*pixel_data)[y][x] = image[y * width + x]; // 1D -> 2D
        }
    }

    // Gaussian blur
    int sigma = 1; // standard deviation
    float gaussian_kernel[3][3] = {
        {1.0 / 16, 2.0 / 16, 1.0 / 16}, //      [1,2,1]
        {2.0 / 16, 4.0 / 16, 2.0 / 16}, //(1/16)[2,4,2]
        {1.0 / 16, 2.0 / 16, 1.0 / 16} //       [1,2,1]
    };
    
    

    
    
    free(pixel_data);
    stbi_image_free(image);
    return 0;
}