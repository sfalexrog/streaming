#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <fstream>

#include "vec3.h"

#include "sampler.h"

/// "Зажимает" значение value в диапазоне [min..max]
int clamp(int value, int min, int max)
{
    return std::min(std::max(value, min), max);
}

int main(int argc, char** argv)
{
    int width, height;
    int components;

    unsigned char *image = stbi_load("gamma_dalai_lama_gray.jpg", &width, &height, &components, 3);

    {
         std::fstream test_out("test_out", std::ios::out);
         test_out << "test" << std::endl;
    }

    if (image == nullptr)
    {
        std::cout << "Failed to open image" << std::endl;
    }
    else
    {
        std::cout << "Image size: " << width << "x" << height << ", components: " << components << std::endl;

        Sampler img{image, width, height, components};

        int swidth = width / 2;
        int sheight = height / 2;
        unsigned char *scaled = new unsigned char[swidth * sheight * components];

        for(int x = 0; x < swidth; ++x)
        {
            for(int y = 0; y < sheight; ++y)
            {
                vec3 color;
                for(int dx = 0; dx < 2; ++dx)
                {
                    for(int dy = 0; dy < 2; ++dy)
                    {
                        color = color + img.at(float(x + dx / 2.0f)/float(swidth), float(y + dy / 2.0f)/float(sheight), true);
                    }
                }
                color = color * (1.0f / 4.0f);
                color = linear_to_gamma(color);
                scaled[(y * swidth * components) + (x * components)    ] = clamp(color.r, 0, 255);
                scaled[(y * swidth * components) + (x * components) + 1] = clamp(color.g, 0, 255);
                scaled[(y * swidth * components) + (x * components) + 2] = clamp(color.b, 0, 255);
            }
        }
        stbi_write_png("dalai_lama.png", swidth, sheight, 3, scaled, 0);
        stbi_image_free(image);        
    }
    return 0;
}
