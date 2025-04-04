## Laplacian Edge Detection on Grayscale Images

implements the Laplacian filter, a second-order derivative operator, to detect edges in a grayscale image.



## Overview
Goal: Identify edges in grayscale images by applying the Laplacian operator after reducing noise via Gaussian smoothing.
The Laplacian is defined mathematically as:
$$\nabla^2 f = \frac{\partial^2 f}{\partial x^2} + \frac{\partial^2 f}{\partial y^2}$$
- This highlights regions with rapid intensity changes (edges), as it captures areas where the gradient itself is changing.

why do this? 
- i was bored
- check out [3b1b video on convolution](https://youtu.be/KuXjwB4LzSA?si=swm99z4ep4S3Yv3L)

### Implementation Details

Tools Used
- stb_image.h / stb_image_write.h for image loading and saving.
- C language for low-level pixel manipulation.
- Tried to use a VLA ended not going cause code memory leaks


## Execution
Before execution check which image you would like to use they are stored in images folder replace this line stbi_load("images/your image name here.png", &width, &height, &channels, 1); with you image name in the marked spot
- default image selected is pilot.png
- If you are using your own image make sure the image is in .png format

```sh
gcc main.c -o laplacian
```
```sh
./laplacian
```



### Stretch Goals:
- Apply Thresholding
- Apply the Laplacian transform in frequency domain using the Fourier Transform (optional but interesting).
- Implement real-time video processing if you have OpenCV or SDL2.
- Compare against the Sobel filter, which detects directional edges