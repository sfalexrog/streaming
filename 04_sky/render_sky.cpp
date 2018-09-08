#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"

#include "camera.h"
#include "sampler.h"

#include <algorithm>

const float Pi = 3.14159265359f;

int clamp(int value, int min, int max)
{
    return std::max(min, std::min(value, max));
}

int main(int argc, char** argv)
{
    int width, height, components;
    vec3 *image = (vec3*) stbi_loadf("../03_images/20060121-06_hd.hdr", &width, &height, &components, 3);

    float yaw = 235.0f;
    float pitch = 0.0f;

    Camera c{vec3{cos(pitch * Pi / 180.0f) * sin(yaw * Pi / 180.0f),
                  sin(pitch * Pi / 180.0f),
                  cos(pitch * Pi / 180.0f) * cos(yaw * Pi / 180.0f)}};

    const int w = 800;
    const int h = 800;

    const float EXPOSITION = 4.0f;

    unsigned char *render = new unsigned char[w * h * 3];
    LinearSampler sky{image, width, height};
    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++x)
        {
            vec3 dir = c.dir * 0.8 + c.up * (float(h / 2 - y) / float(h)) + c.right * (float(x - w/2) / float(w));
            dir = norm(dir);
            float phi = std::asin(dir.y);
            float theta = std::atan2(dir.z, dir.x);

            float u = (theta + Pi) / (Pi * 2.0f);
            float v = 0.5 - phi / Pi;

            vec3 col = sky.at(u, v) * EXPOSITION;
            vec3 col_tonemapped = vec3{
                col.r / (1.0f + col.r),
                col.g / (1.0f + col.g),
                col.b / (1.0f + col.b)
            };
            vec3 cg = linear_to_gamma(col) * 255.0f;
            render[(y * w * 3) + (x * 3)] = clamp(cg.r, 0, 255);
            render[(y * w * 3) + (x * 3) + 1] = clamp(cg.g, 0, 255);
            render[(y * w * 3) + (x * 3) + 2] = clamp(cg.b, 0, 255);
        }
    }

    stbi_write_png("output.png", w, h, 3, render, 0);
    delete render;
    return 0;
}

