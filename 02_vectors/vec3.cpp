#include "vec3.h"
#include <cmath>

std::ostream& operator<<(std::ostream& s, const vec3& v)
{
    s << "[ " << v.x << ", " << v.y << ", " << v.z << "]";
    return s;
}

vec3 norm(const vec3& v)
{
    return v * (1 / len(v));
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.y * v2.z - v2.y * v1.x,
                v2.x * v1.z - v1.x * v2.z,
                v1.x * v2.y - v2.x * v1.y);

}

float len(const vec3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
