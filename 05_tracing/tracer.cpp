#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"
#include "sphere.h"
#include "hit_result.h"

#include "sampler.h"

#include "camera.h"

#include <vector>

struct Scene
{
    std::vector<sphere> spheres;

    Scene() : spheres() {}

    void add(const sphere &s)
    {
        spheres.push_back(s);
    }

    hit_result intersect(const ray &r)
    {
        hit_result hr;
        hr.hit = false;
        for(auto& s : spheres)
        {
            hit_result shr = s.hit(r);
            if (shr.hit)
            {
                shr.hit_sphere = &s;
                return shr;
            }
        }
        return hr;
    }
};

const float Pi = 3.14159265359f;

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 800;
    unsigned char *pixels = new unsigned char[WIDTH * HEIGHT * 3];
    vec3 *colors = new vec3[WIDTH * HEIGHT];

    float yaw = -15.0f;
    float pitch = -30.0f;

    Camera c{vec3{2.0f, 5.0f, -2.0f},
            vec3{cos(pitch * Pi / 180.0f) * sin(yaw * Pi / 180.0f),
                 sin(pitch * Pi / 180.0f),
                 cos(pitch * Pi / 180.0f) * cos(yaw * Pi / 180.0f)}};

    Scene s;
    s.add(sphere(vec3{0.0f, 0.0f, 2.0f}, 1.0f, vec3{1.0f, 0.0f, 0.0f}));
    s.add(sphere(vec3{2.0f, 0.0f, 2.0f}, 0.5f, vec3{0.0f, 1.0f, 0.0f}));
    s.add(sphere(vec3{0.0f, 2.0f, 2.0f}, 0.5f, vec3{0.0f, 0.0f, 1.0f}));
    s.add(sphere(vec3{0.0f, -50.0f, 0.0f}, 50));
    
    for(int y = 0; y < HEIGHT; ++y)
    {
        for(int x = 0; x < WIDTH; ++x)
        {
            vec3 rd = c.dir + c.left * (float(WIDTH / 2 - x) / float(WIDTH / 2)) + c.up * (float(HEIGHT / 2 - y) / float(HEIGHT / 2));

            ray r{
                c.pos,
                rd
            };

            hit_result hr = s.intersect(r);
            if (hr.hit)
            {
                colors[y * WIDTH + x] = hr.hit_sphere->color;
            }
            else
            {
                colors[y * WIDTH + x] = vec3{0.0f, 0.0f, 0.0f};
            }
        }
    }

    for(int y = 0; y < HEIGHT; ++y)
    {
        for(int x = 0; x < WIDTH; ++x)
        {
            vec3 c = colors[y * WIDTH + x];
            vec3 color_tonemapped{
                c.r / (1.0f + c.r),
                c.g / (1.0f + c.g),
                c.b / (1.0f + c.b)
            };
            vec3 cg = linear_to_gamma(color_tonemapped);
            pixels[(y * WIDTH + x) * 3    ] = cg.r * 255;
            pixels[(y * WIDTH + x) * 3 + 1] = cg.g * 255;
            pixels[(y * WIDTH + x) * 3 + 2] = cg.b * 255;
        }
    }

    stbi_write_png("output.png", WIDTH, HEIGHT, 3, pixels, 0);
    delete[] pixels;
    delete[] colors;

    return 0;
}
