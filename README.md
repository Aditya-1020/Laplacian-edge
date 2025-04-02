Project: Laplacian Edge Detection on Grayscale Images

Implementation of Laplacian filter to detect edges in a grayscale image.
- using second order derivative filter

## Steps:
1. Load an Image: Use a library like stb_image.h (or raw PGM format if you want to avoid external libraries).
2. Convert to Grayscale (if needed): If the image is RGB, average the R, G, and B values.
3. Apply a 3x3 Laplacian Kernel: Convolve the image with the Laplacian filter:
    - \begin{bmatrix} 0 &amp; 1 &amp; 0 \\ 1 &amp; -4 &amp; 1 \\ 0 &amp; 1 &amp; 0 \end{bmatrix}
    or \begin{bmatrix} 1 &amp; 1 &amp; 1 \\ 1 &amp; -8 &amp; 1 \\ 1 &amp; 1 &amp; 1 \end{bmatrix}
4. Handle Boundary Pixels: Use zero-padding, mirroring, or ignore them.
5. Normalize and Threshold: Normalize output values to 0–255 and apply a threshold for better visibility.
6. Save the Processed Image: Save the output as a PGM file (or PNG if using a library).



### Stretch Goals:
- Apply the Laplacian transform in frequency domain using the Fourier Transform (optional but interesting).
- Implement real-time video processing if you have OpenCV or SDL2.
- Compare against the Sobel filter, which detects directional edges