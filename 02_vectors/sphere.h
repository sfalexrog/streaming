#pragma once

#include "vec3.h"
#include "hit_result.h"
#include "ray.h"

struct sphere
{
    vec3 c;
    float r;

    sphere(vec3 center, float radius) : c(center), r(radius) {}

    hit_result hit(const ray& r) const;

    vec3 normal_at(vec3 p) const;

};
