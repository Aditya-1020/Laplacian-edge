#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include "src/stb_image.h"
#include "src/stb_image_write.h"

int main(void) {
    int width, height, channels;

    // Load image in grayscale (1 channel)
    unsigned char *image = stbi_load("images/pilot.png", &width, &height, &channels, 1);
    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }
    printf("Loaded image: %d x %d, Channels: %d\n", width, height, channels);

    // Allocate memory for pixel data as int[]
    int *pixel_data = malloc(sizeof(int) * width * height);
    if (!pixel_data) {
        fprintf(stderr, "Memory allocation failed for pixel_data.\n");
        stbi_image_free(image);
        return 1;
    }

    // Copy grayscale image to pixel_data[]
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixel_data[y * width + x] = image[y * width + x];
        }
    }

    // Gaussian blur kernel
    float gaussian_kernel[3][3] = {
        {1.0f / 16, 2.0f / 16, 1.0f / 16},
        {2.0f / 16, 4.0f / 16, 2.0f / 16},
        {1.0f / 16, 2.0f / 16, 1.0f / 16}
    };

    // Allocate float arrays for intermediate and final results
    float *smooth_image = malloc(sizeof(float) * width * height);
    float *edge_image = malloc(sizeof(float) * width * height);
    if (!smooth_image || !edge_image) {
        fprintf(stderr, "Memory allocation failed for intermediate images.\n");
        free(pixel_data);
        stbi_image_free(image);
        return 1;
    }

    // Apply Gaussian blur (skip borders)
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            float result = 0.0f;

            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    int pixel = pixel_data[(i + ki) * width + (j + kj)];
                    float weight = gaussian_kernel[ki + 1][kj + 1];
                    result += pixel * weight;
                }
            }

            smooth_image[i * width + j] = result;
        }
    }

    // Laplacian kernel for edge detection
    float laplacian_kernel[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    // Apply Laplacian (again, skip borders)
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            float result = 0.0f;

            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    float pixel = smooth_image[(i + ki) * width + (j + kj)];
                    float weight = laplacian_kernel[ki + 1][kj + 1];
                    result += pixel * weight;
                }
            }

            edge_image[i * width + j] = result;
        }
    }

    // Normalize to 0–255
    float min_val = edge_image[0];
    float max_val = edge_image[0];

    for (int i = 0; i < width * height; i++) {
        if (edge_image[i] < min_val) min_val = edge_image[i];
        if (edge_image[i] > max_val) max_val = edge_image[i];
    }

    // Allocate final image buffer
    unsigned char *output_image = malloc(sizeof(unsigned char) * width * height);
    if (!output_image) {
        fprintf(stderr, "Memory allocation failed for output image.\n");
        free(pixel_data); free(smooth_image); free(edge_image);
        stbi_image_free(image);
        return 1;
    }

    for (int i = 0; i < width * height; i++) {
        float normalized = ((edge_image[i] - min_val) / (max_val - min_val)) * 255.0f;
        if (normalized < 0) normalized = 0;
        if (normalized > 255) normalized = 255;
        output_image[i] = (unsigned char)(normalized);
    }

    // Save final PNG image
    stbi_write_png("edges.png", width, height, 1, output_image, width);
    printf("Final image 'edges.png' created successfully.\n");

    // Free memory
    free(pixel_data);
    free(smooth_image);
    free(edge_image);
    free(output_image);
    stbi_image_free(image);

    return 0;
}
// if you are reading this dont do it this shit was hard