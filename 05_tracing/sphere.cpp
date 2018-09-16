#include "sphere.h"
#include <cmath>

hit_result sphere::hit(const ray& R) const
{
    hit_result hr;

    float A = R.direction * R.direction;
    float B = R.direction * (R.origin - c) * 2;
    float C = (R.origin - c) * (R.origin - c) - (r * r);

    float D = B * B - 4 * A * C;
    if (D < 0) {
        hr.hit = false;
    } else if (D == 0) {
        hr.hit = true;
        float t = -B / (2 * A);
        hr.distance = t * len(R.direction);
        hr.hit_pt = R.origin + R.direction * t;
    } else {
        hr.hit = true;
        float t1 = (-B - std::sqrt(D)) / (2 * A);
        float t2 = (-B + std::sqrt(D)) / (2 * A);
        if (t1 >= 0) {
            hr.distance = t1 * len(R.direction);
            hr.hit_pt = R.origin + R.direction * t1;
        } else if (t2 >= 0) {
            hr.distance = t2 * len(R.direction);
            hr.hit_pt = R.origin + R.direction * t2;
        } else {
            hr.hit = false;
        }
    }
    return hr;
}

vec3 sphere::normal_at(vec3 p) const
{
    vec3 R = p - c;
    return norm(R);
}
