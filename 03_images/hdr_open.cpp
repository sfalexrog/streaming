#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "vec3.h"
#include "sampler.h"

int clamp(int value, int min, int max)
{
    return std::min(std::max(value, min), max);
}

int main(int argc, char** argv)
{
    int width, height;
    int components;
    vec3 *image = (vec3*)stbi_loadf("20060121-06_hd.hdr", &width, &height, &components, 3);

    if (image == nullptr)
    {
        std::cout << "Unable to load image" << std::endl;
        return 1;
    }

    unsigned char *ldr = new unsigned char[width * height * components];

    const float EXPOSURE = 8.0f;

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            vec3 c = image[y * width + x];
            c = c * EXPOSURE;
            c = vec3{c.r / (1.0f + c.r),
                     c.g / (1.0f + c.g),
                     c.b / (1.0f + c.b)
            };
            vec3 cg = linear_to_gamma(c);
            ldr[(y * width * components) + (x * components)    ] = clamp(cg.r * 255.0f, 0, 255);
            ldr[(y * width * components) + (x * components) + 1] = clamp(cg.g * 255.0f, 0, 255);
            ldr[(y * width * components) + (x * components) + 2] = clamp(cg.b * 255.0f, 0, 255);
        }
    }

    stbi_write_png("20060121-06_hd.png", width, height, components, ldr, 0);
    delete ldr;
    stbi_image_free(image);
    return 0;
}
