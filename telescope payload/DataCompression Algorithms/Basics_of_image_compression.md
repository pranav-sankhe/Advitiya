# Basic Image Compression Algorithms 

Because of the explosively increasing information of image and video in various storage devices and Internet, the image and video compression technique becomes more and more important 

The basic idea of data compression is to reduce the data correlation.
By applying Discrete Cosine Transform (DCT), the data in time (spatial) domain can be transformed into frequency domain. Because of the less sensitivity of human vision in higher frequency, we can compress the image or video data by suppressing its high frequency components. 

Moving pictures such as video are data in three-dimensional space consists of spatial plane and time axis. Therefore, in addition to reducing spatial correlation, we need to reduce the time correlation. We introduce a method called Motion Estimation (ME).

Encoder receives the target image, it converts the image into bit stream
b. On the other hand, the decoder receives the bit stream and then converts it back to the image I. If the quantity of bit stream 'b' less than the original image then we call this process Image Compression Coding.

In order to evaluate the coding efficiency, we need a method to evaluate the degree of distortion. There are two common evaluation tools, which are Mean Square Error (MSE) and Peak Signal to Noise Ratio (PSNR). They are defined as following: 

![MSE](https://github.com/sabSAThai/Advitiya/blob/master/images/MSE.png)

![PSNR](https://github.com/sabSAThai/Advitiya/blob/master/images/PSNR.png)

In MSE, f(x,y) f'(x,y) denote the original image and decoded image, respectively. The image size is
WxH . 
The given PSNR formula is common used for 8-bits image. Note that the larger the PSNR, that smaller the degree of
distortion. 

The image coding algorithm today consists of reducing correlation between pixels, quantization and entropy coding. We will discuss these parts one by one in the following chapters. The coding algorithm system model is shown below:

![algo flow](https://github.com/sabSAThai/Advitiya/blob/master/images/Algo_model.png)

## Orthogonal Transform and Discrete Cosine Transform

### Linear transformation
	 It is very useful to represent signals in basis form.

### Orthogonal Transformation
	Any vector in the space can be expressed as the combination of three independent vectors. If we choose these three independent vectors such that they are mutually independent, we will have many useful properties and the numerical computation will become easier. 

	- a1 = x.v1
	- a2 = x.v2
	- a3 = x.v3

### Karhunen-Loeve Transformation 

Because images have high correlation in a small area, for an image with size K1xK2 , we usually divide it into several small blocks with size N1xN2 and we deal with each block with a transformation that can reduce its pixel correlation separately.
The trade off here is if we choose bigger block size we may obtain higher compression ratio. However, an oversized block size may have lower pixel correlation.

In order to do linear transformation to each block in the image, we may scan the pixel in the transformation blocks and transform it into an N dimensional vector. The number of total transformation blocks equals to M = K1K2/N1N2 and the number of pixels in a transformation block is N = N1N2. After horizontal scanning, we have M vectors:

![M_vectors](https://github.com/sabSAThai/Advitiya/blob/master/images/M_vectors.png)

What we want the do is to achieve the optimal orthogonal transform for these vectors in order to reduce the pixel correlation in each transformation blocks. That is, find a transformation matrix V such that :

![V_transformation](https://github.com/sabSAThai/Advitiya/blob/master/images/V_transformation.png)

Now consider the covariance of vectors x and y. 

![covariance_x_y.png](https://github.com/sabSAThai/Advitiya/blob/master/images/covariance_x_y.png)

We can write y as :

![y](https://github.com/sabSAThai/Advitiya/blob/master/images/y.png)

Therefore the mean of y is : 

![mean_y](https://github.com/sabSAThai/Advitiya/blob/master/images/mean_y.png)

To make our life simple we assume each pixel value is subtracted with its mean value. 
Therefore, 

![new_c](https://github.com/sabSAThai/Advitiya/blob/master/images/new_c.png)

We can write the above equations in matrix form : 

![new_c](https://github.com/sabSAThai/Advitiya/blob/master/images/matrix_C.png)

These are called a covariance matrix. We can easily find that it must be a symmetric matrix. 
They can be rewritten in a vector form:

![vector_C](https://github.com/sabSAThai/Advitiya/blob/master/images/vector_C.png)

We know that y has been obtained after applying orthogonal transformation matrix "V" on x . 
Therefore we can write Cyy as : 

![Cyy](https://github.com/sabSAThai/Advitiya/blob/master/images/Cyy.png)

The purpose is to obtain uncorrelated y^(m). Note that for an uncorrelated y^(m),  it has
a covariance matrix Cyy which is a diagonal matrix. 
</br>
Now if Cyy is a diagonal matrix, then based on the expression of Cyy, we can say that it is is the
eigenvalue-eigenvector decomposition of Cxx.  The matrix V is composed of the eigenvectors of Cxx. 
Usually, we have it ordered with eigenvectors that have bigger corresponding eigenvalues to smaller ones.

</br>
This is called the Karhunen-Loeve Transform (KLT). 


### Discrete Cosine Transform

For common used such as JPEG standard or MPEG standard, we do not use KLT. Although we can have the optimal orthogonal transformation by applying KLT, it still has the following drawbacks:

- Each image has to do the KLT respectively. This makes the computation complexity large. 

- In order to decode the encoded image we have to transmit the KLT transformation matrix to the decoder. It costs another process time and memory spaces. 

Then we have the Discrete Cosine Transform (DCT).
The forward DCT is defined as : 

![DCT](https://github.com/sabSAThai/Advitiya/blob/master/images/DCT.png)

And the inverse DCT is defined as the following equation:

![inverse_DCT.png](https://github.com/sabSAThai/Advitiya/blob/master/images/inverse_DCT.png)


The F(u,v) is called the DCT coefficient, and the basis of DCT is:

![DCT_coff.png](https://github.com/sabSAThai/Advitiya/blob/master/images/DCT_coff.png)

Then we can rewrite the Invesre Discrete Cosine Transform as follows:

![New_Inverse_DCT.png ](https://github.com/sabSAThai/Advitiya/blob/master/images/New_Inverse_DCT.png)

The 8x8 two dimensional DCT basis is depicted below: 

![8x8_DCT.png](https://github.com/sabSAThai/Advitiya/blob/master/images/8x8_DCT.png)

###  Quantization
The transformed 8x8 block in above figure now consists of 64 DCT coefficients. The first coefficient F(0,0)
is the DC component and the other 63 coefficients are AC component. The DC component F(0,0) is essentially the sum of the 64 pixels in the input 8x8 pixel block multiplied by the scaling factor (1/4)*C(0)C(0) = 1/8. 








