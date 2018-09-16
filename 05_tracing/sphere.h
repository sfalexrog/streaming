#pragma once

#include "vec3.h"
#include "hit_result.h"
#include "ray.h"

struct sphere
{
    vec3 c;
    float r;

    vec3 color;    

    sphere(const vec3 &center, float radius, const vec3 &color = vec3{1.0f, 1.0f, 1.0f}) : c(center), r(radius), color(color) {}

    hit_result hit(const ray& r) const;

    vec3 normal_at(vec3 p) const;

};
