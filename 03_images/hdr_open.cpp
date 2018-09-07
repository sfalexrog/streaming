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
    vec3 *image = (vec3*)stbi_loadf("grace-new.hdr", &width, &height, &components, 3);

    if (image == nullptr)
    {
        std::cout << "Unable to load image" << std::endl;
        return 1;
    }

    unsigned char *ldr = new unsigned char[width * height * components];

    Sampler s{nullptr, 0, 0, 0};
    const float EXPOSURE = 128.0f;

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            vec3 c = image[y * width + x];
            c = s.gamma_to_linear(c);
            c = c * EXPOSURE;
            //vec3 cg = s.linear_to_gamma(c);//c;//s.linear_to_gamma(c);
            vec3 cg = c;
            ldr[(y * width * components) + (x * components)] = clamp(cg.r, 0, 255);
            ldr[(y * width * components) + (x * components) + 1] = clamp(cg.g, 0, 255);
            ldr[(y * width * components) + (x * components) + 2] = clamp(cg.b, 0, 255);
        }
    }

    stbi_write_png("grace-new.png", width, height, components, ldr, 0);
    delete ldr;
    stbi_image_free(image);
    return 0;
}
