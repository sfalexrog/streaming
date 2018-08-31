#pragma once

#include "vec3.h"

struct hit_result
{
    bool hit; // Было ли пересечение?
    float distance; // Расстояние, которое прошёл луч
    vec3 hit_pt; // Точка пересечения
};
