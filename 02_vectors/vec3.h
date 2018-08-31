#pragma once

#include <iostream>

struct vec3
{
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator-() const  { return vec3(-x, -y, -z); }
    vec3 operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
    vec3 operator-(const vec3& other) const { return *this + (-other); }

    vec3 operator*(const float c) const { return vec3(x * c, y * c, z * c); }
    float operator*(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }
};

std::ostream& operator<<(std::ostream& s, const vec3& v); 

vec3 norm(const vec3& v);
vec3 cross(const vec3& v1, const vec3& v2);
float len(const vec3& v);
