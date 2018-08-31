#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"
#include "sphere.h"


int main(int argc, char** argv)
{
    vec3 eye = vec3(0, 0, -1);
    sphere s(vec3(0, 0, 1), 1);

    vec3 up = vec3(0, 1, 0);
    vec3 left = vec3(1, 0, 0);
    vec3 front = vec3(0, 0, 1);

    const int width = 800;
    const int height = 800;
    const int colors = 3;

    unsigned char image[width * height * colors];

    for(int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if ((x == width / 2) && (y == height / 2))
            {
                std::cout << "center" << std::endl;
            }
            vec3 direction = up * (float(height / 2 - y) / float(height / 2))
                           + left * (float(width / 2 - x) / float(width / 2))
                           + front;
            ray r(eye, direction);
            hit_result hr = s.hit(r);
            if (hr.hit)
            {
                vec3 n = s.normal_at(hr.hit_pt);
                image[(y * width * colors) + (x * colors)] = (0.5f + n.x * 0.5f) * 255;
                image[(y * width * colors) + (x * colors) + 1] = (0.5f + n.y * 0.5f) * 255;
                image[(y * width * colors) + (x * colors) + 2] = (0.5f + n.z * 0.5f) * 255;
            }
            else
            {
                image[(y * width * colors) + (x * colors)] = 0;
                image[(y * width * colors) + (x * colors) + 1] = 0;
                image[(y * width * colors) + (x * colors) + 2] = 0;
            }
        }
    }
    
    stbi_write_png("output.png", width, height, colors, image, 0);

    return 0;
}
