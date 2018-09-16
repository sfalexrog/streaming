#pragma once

#include "vec3.h"

struct ray
{
    vec3 origin;
    vec3 direction;

    ray(vec3 origin, vec3 direction) : origin(origin), direction(norm(direction)) {}
};