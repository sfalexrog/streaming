#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main(int argc, char** argv)
{
    /**
     * RGBRGBRGB...
     * 888 
     */
    const int channels = 3;
    const int width = 800;
    const int height = 800;
    unsigned char image[channels * width * height];

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            /*
            image[(y * width * channels) + (x * channels)] = 255; // R
            image[(y * width * channels) + (x * channels) + 1] = (255 * x) / width; // G
            image[(y * width * channels) + (x * channels) + 2] = 255 * (height - y) / height; // B
            */
           for (int c = 0; c < channels; ++c)
           {
                image[(y * width * channels) + (x * channels) + c] = 0;
           }
        }
    }

    for (int y = 0; y < height; y += 2)
    {
        for (int x = 0; x < width / 2; ++x)
        {
           for (int c = 0; c < channels; ++c)
           {
                image[(y * width * channels) + (x * channels) + c] = 255;
           }
        }
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = width / 2; x < width; ++x)
        {
           for (int c = 0; c < channels; ++c)
           {
                image[(y * width * channels) + (x * channels) + c] = 185 ;
           }
        }
    }

    stbi_write_png("hello.png", width, height, channels, image, 0);

    return 0;
}
