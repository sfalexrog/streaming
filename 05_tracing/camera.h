#pragma once

#include "vec3.h"

struct Camera
{
    // Направление "вперёд"
    vec3 dir;
    // Направление "влево"
    vec3 left;
    // Направление "вверх"
    vec3 up;

    // Положение камеры
    vec3 pos;

    Camera(const vec3& position, const vec3& desired_dir, const vec3& desired_up = vec3{0.0f, 1.0f, 0.0f})
    {
        pos = position;
        dir = norm(desired_dir);
        left = norm(cross(dir, desired_up));
        up = cross(left, dir);
    }
};
