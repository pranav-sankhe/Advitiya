# Analysis of various astronomical image compression algorithms

## Abstract of the analysis :

We compare a variety of lossless image compression methods on a large sample of astronomical images and show how the compression ratios and speeds of the algorithms are affected by the amount of noise (that is, entropy) in the images.

We perform image compression tests on a large sample of 16-bit integer astronomical CCD
images using the GZIP compression program and using a newer FITS tiled-image compression
method that currently supports 4 compression algorithms: Rice, Hcompress, PLIO, and the same
Lempel-Ziv algorithm that is used by GZIP. Overall, the Rice compression algorithm strikes the
best balance of compression and computational efficiency; it is 2–3 times faster and produces
about 1.4 times greater compression than GZIP (the uncompression speeds are about the same).
The Rice algorithm has a measured K value of 1.2 bits per pixel, and thus produces 75%–90%
(depending on the amount of noise in the image) as much compression as an ideal algorithm with
K = 0. Hcompress produces slightly better compression but at the expense of 3 times more CPU
time than Rice. 

</br>

Compression tests on a sample of 32-bit integer images show similar results, but
the relative speed and compression ratio advantage of Rice over GZIP is even greater. 


## Compression Methods

We follow the FITS tiled image compression convention model.
Under this convention, the image is first divided into a rectangular grid of “tiles”.
Each tile of pixels is then compressed using one of several available compression algorithms
(described below), and the compressed stream of bytes is stored in a variable length array column in a FITS binary table. Each row of the FITS binary table corresponds to one tile in the image. 

## Desciption of Compression Algorithms

### Rice :

The Rice algorithm (Rice et al. 1993; White & Becker 1998) is very simple (additions, subtractions, and some bit masking and shifts), making it computationally efficient. In fact, it has been implemented in hardware for use on spacecraft and in embedded systems, and has been considered for use in compressing images from future space telescopes (Nieto-Santisteban et al. 1999). In its usual implementation, it encodes the differences of consecutive pixels using a variable number of bits. Pixel differences near zero are coded with few bits and large differences require more bits. The algorithm adapts to the noise by determining the number of pure noise bits to strip off the bottom of the difference and include directly in the output bitstream (with no coding). The best value for this noise scale is computed independently for each block of 16 or 32 pixels. With such short blocks, the algorithm requires little memory and adapts quickly to any variations in pixel statistics across the image.

### Hcompress:

The Hcompress algorithm was written to compress the Space Telescope Science Institute digitized sky survey images (White et al. 1992). It involves (1) a wavelet transform called the H-transform (a Haar transform generalized to two dimensions), followed by (2) an optional quantization that discards noise in the image while retaining the signal on all scales, followed by (3) a quadtree coding of the quantized coefficient bitplanes. In this study we omitted the quantization step, which makes Hcompress lossless. The H-transform computes sums and differences within pixel blocks, starting with small 2 × 2 blocks and then increasing by factors of two to 4 × 4, 8 × 8, etc., blocks. This is an exactly reversible, integer arithmetic operation, so a losslessly encoded set of the H-transform coefficients can be uncompressed and inversely transformed to recover the original image. The H-transform can be performed in-place in memory and requires enough memory to hold the original image (or image tile). To avoid overflow problems when summing the pixel values, the memory array is expanded by a factor of two so that each pixel has twice as many bits as in the original image. The Hcompress bitplane coding, which proceeds by first compressing the most significant bit of each coefficient (mostly zeros) and working down to the least significant bit (usually noise), has the effect of ordering the image description so that the data stream gives a progressively better approximation to the original image as more bits are received. This was used to create an efficient adaptive scheme for image transmission (Percival & White 1996).


### PLIO:

The IRAF (Tody 1993) Pixel List I/O (PLIO) algorithm was developed to store integer image masks in a compressed form. This special-purpose run-length encoding algorithm is very effective on typical masks consisting of isolated high or low values embedded in extended regions that have a constant pixel value. Our implementation of this algorithm only supports pixel values in the range 0 to 2^(23). Because of the specialized nature of the PLIO algorithm, we only discuss its use with compressing data masks, in § 4.3.

### GZIP

The popular GZIP file compression utility (Gailly & Adler 1992) is the de facto standard compression method currently used in the astronomical community. Nearly all major observatories and data archive centers distribute their data as GZIP-compressed files. For this reason, GZIP serves as the baseline of comparison for the other compression methods in our study. GZIP uses a variation of the Lempel-Ziv algorithm (Ziv & Lempel 1977) to build a dictionary of repeated sequences of bytes occurring in the input and using a short code for each sequence. The most important distinguishing characteristic of GZIP compared to the other compression algorithms used in this study is that GZIP treats each 8-bit byte of the input data stream as an independent datum, whereas the other compression methods operate on the numerical value of the input image pixels as multibyte quantities. This puts GZIP at a distinct disadvantage when compressing astronomical images with 16-bit or 32-bit pixel values because, unlike the Rice and Hcompress algorithms, GZIP cannot use the numerical difference between adjacent pixels as a means of improving the compression. As a result, it becomes less effective when increasing noise makes repeated bit patterns less common.
</br>
It should be noted that the GZIP algorithm has a user-selectable parameter for fine tuning the trade off between speed and compression ratio. 


