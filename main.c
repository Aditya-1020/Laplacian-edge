#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
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
    int (*pixel_data)[width][height] = malloc(sizeof(int[width][height])); // creates 2D pointer to an array
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

    float smooth_image[height][width];
    
    for (int i = 1; i < height - 1; i++) { // avoids border
        for (int j = 1; j < width - 1; j++) {
            float result = 0.0;
    
            // applying gaussian kernel
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    int pixel = (*pixel_data)[i + ki][j + kj];
                    float weight = gaussian_kernel[ki + 1][kj + 1];
                    result += pixel * weight;
                }
            }

            smooth_image[i][j] = result;
        }
    }
    
    // Applying Laplacian
    float laplacian_kernel[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    float edge_image[height][width];
    
    for (int i = 1; i < height - 1; i++) { // avoids border
        for (int j = 1; j < width - 1; j++) {
            float result = 0.0;
    
            // applying laplacian kernel
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    int pixel = smooth_image[i + ki][j + kj];
                    float weight = laplacian_kernel[ki + 1][kj + 1];
                    result += pixel * weight;
                }
            }
            edge_image[i][j] = result;
        }
    }

    // Normalizing

    float min_val = edge_image[0][0];
    float max_val = edge_image[0][0];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (edge_image[i][j] < min_val)
            min_val = edge_image[i][j];
            if (edge_image[i][j] > max_val)
            max_val = edge_image[i][j];
        }
    }

    unsigned char output_image[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float pixel = edge_image[i][j];
            float normalized = ((pixel - min_val) / (max_val - min_val)) * 255.0;

            // In case of small rounding errors
            if (normalized < 0) normalized = 0;
            if (normalized > 255) normalized = 255;

            output_image[i][j] = (unsigned char) normalized; // no negative
        }
}
    stbi_write_png("edges.png", width, height, 1, output_image, width);
    

    // Thresholding

    /*
    if(pixel_value < threshold)
        output_pixel = background_value;
    else
        output_pixel = 225; */

    free(pixel_data);
    stbi_image_free(image);
    return 0;
}