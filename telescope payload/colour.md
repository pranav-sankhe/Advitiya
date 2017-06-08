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
