# Astronomical Image Filtering
 
## Astronomical Images
 
Images of astronomical objects are usually taken with electronic detectors such as a CCD (Charge Coupled Device). Similar detectors are found in normal digital cameras. Telescope images are nearly always greyscale, but nevertheless contain some colour information. An astronomical image may be taken through a colour filter. Different detectors and telescopes also usually have different sensitivities to different colours (wavelengths).

The key to processing images is to have a clear idea of your objective. Do you want to produce "a pretty picture" or bring out some specific detail or feature of the target object? Is colour important or will black and white be sufficient?. With a clear objective in mind consider the various types of processing possible.

First we will go through a general flow which will present an overview of the methodology to be adopted for astronomical image processing. Then we will dig into the details of each an every process. 

So let's march in !

## Calibration

Calibration is the process of removing unwanted signals from the raw images. Calibration is a must prior to further processing of images.

## Quality Assessment

You will want to select only the best of your captured images for processing. The best way is to look at each image and discard those that are not clear, sharp, well shaped etc. Even with video it can be worth the time to go through and select just a few really good frames rather than rely on the 'quality' ranking provided by your processing software. 


## Resampling (Resizing)

You may wish to enlarge the images by a factor (say x1.5 or x2.0).Now obviously this will not improve the level of detail in each image but it will spread the detail over more pixels. This may be of benefit by allowing the alignment and stacking process (see below) to achieve "sub pixel" precision so that the resulting stacked image has finer detail than any of the original images. An enlarged image may also work better with sharpening filters. Resample (resize) back to the original (or any other desired) size later in processing. As we go through the whole process the importance of resampling (resizing) the image will be emphasized. 

## Alignment

You will have captured multiple images (or a video) of your target object. All frames will need to be aligned and stacked. Alignment is the process of shifting each image up/down and left/right so that the target object is in exactly the same place on every image. There are several ways of doing this provided in astro-imaging software:

Manual: You have to click in exactly the same place (e.g. a star) in each image to set the alignment point.
Centroid: You click on the same star in each image and the software will try to align the centre of the star.
Automatic: (e.g using FFT algorithm) you select a suitable star or image feature and the software will do its best to align the feature on each image.
Some software will allow you to select two points in each image and will rotate the images to compensate for images taken using an alt/azimuth mounted telescope. Registax allows you to select multiple points in the image and can align different areas of the image differently. This can be quite useful when poor "seeing" has caused areas of the image to shimmer.

**Note** : For video, manual alignment is usually impractical because of the number of frames. 


## Stacking

Once the images have been aligned then they can be stacked by:
1. **Averaging (Median)** : This is the normal way to stack images. Each pixel is set to the median value of the appropriate pixels from all the images. Noise is effectively reduced by averaging and there is no danger of any pixels becoming saturated.
 
2. **Adding (Sum)** : The images are added together and pixel values are the sum of the appropriate pixel on all the images. Generally this is not a good idea as bright spots (e.g. stars) will add up to more than the maximum value of a pixel causing distortion or "white out" or areas of the image. But if you have a limited number of images and their maximum pixel values are low then adding can be a useful because it will give a greater range of pixel values for subsequent contrast enhancement.
 
3 **Drizzle** : This is a technique designed by NASA to sharpen images acquired by the Hubble Space Telescope. The objective is to combine the information in multiple images to get a better resolution than the number of pixels in the camera. It is only relevant when the resolution of the telescope is better than the resolution of the CCD. We will go into detailed description of the process somewhere down the lane. The output image is larger than the input image thus possibly may have better resolution than individual input images.     


## Contrast and Colour

__Discussion on colour__ : 

### Optical Spectrum

The visible (optical) spectrum consists of light with wavelengths between about 380nm (deep violet) to about 750nm (deep red). It includes all the colours in the rainbow.

However, many of the colours we perceive with our eyes are not included in the visible spectrum but consist of a mixture of light with different wavelengths. Our brains interpret the mixture as the colour we perceive.

A CCD camera is sensitive to light across the visible spectrum although its sensitivity may vary through the range of wavelengths. CCDs are often sensitive to part of the Infra Red spectrum.

### Red Green Blue (RGB)

It is possible to produce all of the colours we can perceive by making an appropriate mixture of red, green and blue.

To produce a coloured astronomical image it is usual to capture three images: one with a red filter in front of the CCD, one with a green filter and one with a blue filter. The three images are then combined to form the coloured (RGB) image. (Some "one shot" colour cameras have a matrix of RGB filters in front of the CCD so they capture and combine the R,G and B images in "one shot").

As the sensitivity of the CCD is different through the three filters we need to be careful how we combine the R, G and B images so that we get the colour balance correct. By "correct" I mean that the resulting colours are seen as close as possible to the way we would see them if we were looking at the object directly. The two main ways to set the colour balance are:

**Theoretical**: If we know the sensitivity of the CCD through each of the filters then we can combine the images in the correct proportion.
**White Balance**: We can adjust the image so that things that we know should be white or grey appear as such.
Most software will provide the ability to to combine R,G & B images and will allow you to adjust the balance or will try to do so automatically using a "white balance" control.

### Luminance (LRGB)

As well as getting the colour of each pixel correct we need to consider how bright it is. It is the contrast in brightness that provides most of the detail in an astronomical image.

The simple way to set the brightness of each pixel is to add up red, green and blue components. If you have a set of R, G and B images and you combine them and get the colour balance correct then the brightness of each pixel should be more or less correct.

Some software will let you specify the proportion of R, G and B you want to use as as the "luminance" or brightness channel separately from the colour balance. For example, if you think the green image has better contrast in detail than the others you can use a greater proportion of green in the luminance (brightness) without actually changing the colour.

As an alternative, you can capture a separate luminance image using a clear filter.

If you capture a CCD image with a clear filter then you get a simple greyscale image. Because the CCD is capturing ALL the light it may be able to obtain a good image of a faint object better than with any of the colour filters. You may be able to use a higher resolution with a clear filter and get more detail.

Now you have luminance, red, green and blue images (LRGB). The RGB images are combined and adjusted to get the best colour balance and the luminance image is used to set the brightness of each pixel.

Some software will build a colour image from LRGB images. In other cases you will need to combine the RGB images then use these as a colour layer on top of the luminance image. If your luminance image is at a higher resolution than you colour image then you will need to resize (enlarge) the colour image first.

### Contrast adjustment.

With an astronomical image you often need to adjust the contrast (or use gamma or histogram controls) to bring out areas of interest. You need to understand how the software is doing this. Having regard for the discussions above about RGB and LRGB:

If software regards your image as an RGB image and you make a contrast adjustment it will adjust the strength of all three colours. This may or may not be what you want. For example it may make the image look unrealistically colourful.
If the software regards your image as an LRGB image and you make a contrast adjustment it will adjust the luminance channel. This may result in the image looking bright but colourless. It pays to experiment for best results.

### Hue, Saturation and Lightness (HSL)

Another way of defining a pixel value is in terms of its hue, saturation and lightness. In this case:

Hue is a numerical value representing the colour to be seen. The values represent all possible combinations of red, green and blue (that can be reproduced by the computer display) not just the colours of the visible spectrum.
Saturation is a value that determines how strong the colour is. For example if the hue is red then a low value of saturation would be a pale pink and a high value of saturation would be a vibrant red. A zero value of saturation will give grey.
Lightness is similar to luminance and determines how bright the colour is. A zero gives black and a maximum value gives the brightest possible pixel of the hue/saturation defined above.
Some software allows you to manipulate the hue saturation and lightness (HSL) of images. It is unusual to adjust the hue as that will destroy the colour balance you worked so hard to get correct originally. Adjusting saturation and lightness is quite often useful when the image appears colourless (or too colourful).

### Cyan, Magenta and Yellow (CMY)

These three colours can also be used, in combination, to produce every colour the human eye can perceive. They are more often used by artists and designers than by astronomers. Many general purpose software packages will allow you to manipulate an image in terms of its CMY components, (or CMYK, where K is equivalent to a separate luminance channel). By all mean experiment - some interesting "false colour" effects can be produced but I would not generally advocate CMY adjustments for astronomical images.

### Infrared

CCDs are often sensitive to some wavelengths beyond red into the infrared area. If you capture an image with no filter then the strength of this light will get added to the red channel of the image. Also, because of the different wavelength, the infrared light may be a bit out of focus and will blur the red image. For this reason it is best to use a clear filter (IR filter) for the luminance image, (unless of course you are looking for infrared ojects!).

If you have a colour camera or have produced a colour image from (L)RGB images then examine the stacked image carefully to see if the colours are correctly aligned. When taking images of objects near the horizon the red, green and blue images may be slightly displaced. This will cause a red tinge on one side of a star/planet and a blue tinge on the other side. Your software should provide the ability to shift the RGB components and get them properly aligned.

### Stretch, Gamma, Balance, Hue and Saturation

Once you have a stacked image, adjust contrast and colour according to the results you require. The most frequently used techniques are:

1. **Stretch** : This resets the top and bottom of the range of pixel values and 'stretches' the range of pixel values in your image. Gradually increase the 'minimum' pixel value until the dark sky background is reasonably black. Gradually reduce the 'maximum' pixel value until bright stars or planetary features are bright but not saturated.

2. **Contrast & Brightness** : This has the same effect as 'stretch' but the controls are different. Gradually increase contrast and adjust brightness to obtain a dark sky and bright stars.

3. **Gamma** : This allows you to increase or decrease the brightness of mid-range pixels without changing the minimum and maximum values. It is useful to accentuate shadows in a planetary image, bring out faint nebulosity or increase the brightness of small stars in a cluster.

4. **Histogram** : This combines stretch and gamma adjustments in a flexible way. You are shown a graph of input-pixel-value and output-pixel-value. To start, the graph is a straight line but you can set it to any shape. The classical "S" shaped curve is often the most effective at bringing out the best in an image. It pays to experiment.

5. **Colour Balance** : If the image has too much red, green or blue in it then a colour balance correction can be applied.

6. **Saturation** : If the image has too little or too much colour then an increase or decrease in saturation can be applied.

7. **Hue**: This will shift the colour of all pixels towards one or other end of the spectrum; generally not a good idea unless you want to create false colour effects.   
It is usually best not to make too dramatic a change in an image in one go. Gradually improve the image using a series of contrast and colour adjustments interspersed with sharpening and noise reduction filters (see below).



## Filters

### Sharpening Filters

The objective is to make stars small and bright and to bring out detail in planetary images. Fuzzy edges need to be made less fuzzy.

1. **High Pass** : (Sharpen) Accentuates the high frequency signals in the image. Makes changes in brightness across the image more stark. Can also accentuate the noise.

2. **Unsharp** : The unsharp mask is one of the most powerful filters for sharpening an image. The image is examined to find edges and for each pixel near an edge a decision is made as to whether it is on the dark side or the light side. Thus fuzzy edges are removed. There are usually three controls:

	-  **Radius** : set this to your best guess as to how many pixels wide the fuzziness is at the edges of stars or features. Adjust up/down for best results.

	- **Strength** : set this to determine how extreme the lightening/darkening of pixels will be near edges. Too much will introduce noise or dark rings round stars.

	- **Clipping** : set this to a value above zero to reduce noise. This control says in effect "if you find a change in pixel value less than clipping value then this is not actually an edge so don't try to sharpen it" 

3. **Wavelets** : The signal in the image is examined at different frequencies and you can chose how much of each frequency you want.

4. **Deconvolution** : There are a number of 'deconvolution' filters such as Maximum Entropy Deconvolution. The theory is complicated but the idea is that if you know (can guess at) the way in which fuzziness was introduced then you can remove it by a series of repetitive processes. 

5. **Erosion** : This filter cuts away at bright edges. The effect is to reduce the size and 'sharpen' stars. This can be useful if large bright stars are spoiling the view of a galaxy or nebula. In fact multiple use of erosion can remove the stars completely! However, remember that the resulting image is not 'correct' and should not be presented as such.

### Noise Reduction Filters

If the image is 'grainy' this is due to random noise. The best way to avoid noise is to average lots of images, but assuming that has been done already then try some filters:

1. **Low pass** : This reduces high frequency signals in the image and can reduce the effect of pixel-to-pixel noise. However it may make the image too fuzzy.

2. **Median/average** : This will set pixels to the median or average value of the pixels in a given radius around them and can reduce high frequency noise. Unfortunately it also reduces detail.

3. **Edge preserving smooth** : In the same way that the unsharp mask looks to accentuate edges this filter looks for edges and smoothes out those areas that are not near an edge. This often works quite well to reduce noise without reducing detail.

4. **Despeckle/Hot Pixel** : can be used to remove hot pixels.


