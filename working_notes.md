Todu
- apply gaussian matrix to the image 
- methods: https://chatgpt.com/share/67eeb2ad-c89c-8006-9e55-44ed3c4e4e84

---

## Notes

VLA (Variable Length Arrays)
- array whose size is determined at runtime rather than compile time.
- useful when dimensions are not fixed


why not use a normal array ?
- normal array's allocate memory on the stack, is limited in size not enough for large images.
- Require width and height to be known at compile time.

Laplacian Kernel
- matrix to approximate second derivative of image
    second derivative of image ?
    - highlights regions with higher intensities (like in math how second derivative gives rate of change over gradient)
        -- aah so laplacian tells the divergence of a gradient \nabla \cdot \nabla = \nabla^2
        why would that be useful ?
        - because edges are locations where the gradient changes
            -- so if you know where the image is changing you can detect edges

Function:-> $Laplace(f) = \dfrac{\partial^{2} f}{\partial x^{2}} + \dfrac{\partial^{2} f}{\partial y^{2}}$


The kernel uses matrix with process called convolution which is for later?
why even use this kernel ?
- simple, efficient
- treats edges in all orientations equally

Convolution ?
C = (f*g) where "*" means convolution
- created by flipping and shifting values for 1D arrays but cases of 2D the diagonal elements are multiplied (x_n $\times$ yn) and all the correspionding diagonals are added and appended to corresponding element
- can be used to even blur images lol -> oh sh*t thats gaussian smoothing i think...
-- so the grid thats being multiplied with the pixel values is called a kernel
now i get it sort of..?
- not to be confused with CNN's which predict the kernel itself

so how is the kernel calculated ?


whats gaussian smoothing before applying laplacian and why ?
laplacian detects edge but is bad at handling noise (noise == bad lol)
- gaussian smoothing essentially blurs the image making it less prominent

applying it
- slide the kernel over each pixel (ie: element in array)
- multiply values with corresponding pixel value
- sum the results and replace the pixel with this weighted sum

Normalizing, Thresholding ?
laplacian kernel creates any values including negative and images only range (0,225)
- So image is scanned to determine lowest (min) and highest (max) pixel values.

normalized pixel value formula : \text{normalized} = \frac{(\text{pixel} - \text{min})}{(\text{max} - \text{min})} \times 255
use this formula to remap each pixel value

Thresholding smooths the image filtering the noise
- threshold is set (betweeen 0-225)
    - pixels below this are set 0
    - pixels above are set 225 or kept as is.. why ?