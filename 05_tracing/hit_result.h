#pragma once

#include "vec3.h"
#include "sphere.h"

struct hit_result
{
    bool hit; // Было ли пересечение?
    float distance; // Расстояние, которое прошёл луч
    vec3 hit_pt; // Точка пересечения
    struct sphere *hit_sphere; // Указатель на сферу, которую пересекли
};
