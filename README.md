Project: Laplacian Edge Detection on Grayscale Images

Implementation of Laplacian filter to detect edges in a grayscale image.
- using second order derivative filter

## Steps:
1. Setup & Image Handling
- Load a grayscale image (PGM is easiest, or use stb_image for PNG/JPG).
- Store pixel data in a 2D array.

2. Define the Laplacian Kernel
- Choose between the 4-neighbor (-4 center) kernel or the 8-neighbor (-8 center) kernel.
- Store the kernel in a 3x3 array.

3. Implement Convolution
- Iterate over each pixel (excluding boundaries).
- Apply the kernel multiplication and summation.
- Store the result in a new image buffer.

4. Normalize and Threshold
- Find the min/max values in the output image.
- Normalize pixel values to 0–255.
- Apply a threshold to enhance edges.

5. Save the Processed Image
Write the new image to a PGM file for viewing.


### Stretch Goals:
- Apply the Laplacian transform in frequency domain using the Fourier Transform (optional but interesting).
- Implement real-time video processing if you have OpenCV or SDL2.
- Compare against the Sobel filter, which detects directional edges