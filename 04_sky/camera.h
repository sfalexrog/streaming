#pragma once

#include "vec3.h"

struct Camera
{
    // Направление "вперёд"
    vec3 dir;
    // Направление "вправо"
    vec3 right;
    // Направление "вверх"
    vec3 up;

    Camera(const vec3& desired_dir, const vec3& desired_up = vec3{0.0f, 1.0f, 0.0f})
    {
        dir = norm(desired_dir);
        right = norm(cross(dir, desired_up));
        up = cross(right, dir);
    }
};
