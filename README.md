Project: Laplacian Edge Detection on Grayscale Images

Implementation of Laplacian filter to detect edges in a grayscale image.
- using second order derivative filter

## Steps:
1. Setup & Image Handling
- Load a grayscale image (PGM recommended, or use stb_image for PNG/JPG).
- Store pixel data in a 2D array for processing.

2. Apply Gaussian Smoothing
- Use a 3x3 or 5x5 Gaussian kernel (e.g., with standard deviation  or σ = 1.0 or 1.4).
- Convolve the image with the Gaussian kernel to reduce noise before edge detection.

3. Define and Apply the Laplacian Kernel
- Choose between:
    - 4-neighbor Laplacian:
        0  1  0  
        1 -4  1  
        0  1  0  
    - 8-neighbor Laplacian:
        1  1  1  
        1 -8  1  
        1  1  1  
- Convolve the smoothed image with the chosen Laplacian kernel.

4. Implement Convolution
- Iterate over each pixel (excluding the boundary pixels).
- Multiply the surrounding pixels by the kernel values and sum them.
- Store the result in a new image buffer.

5. Normalize and Threshold
- Find the minimum and maximum pixel values in the output image.
- Normalize the pixel values to a 0–255 range.
- Apply an optional threshold to enhance edges further.

6. Save the Processed Image
- Write the processed image to a PGM file (or another format) for visualization.


### Stretch Goals:
- Apply the Laplacian transform in frequency domain using the Fourier Transform (optional but interesting).
- Implement real-time video processing if you have OpenCV or SDL2.
- Compare against the Sobel filter, which detects directional edges
