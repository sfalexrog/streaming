#pragma once
#include <cmath>
#include <algorithm>
#include "vec3.h"

const float GAMMA = 2.2f;

// Переводит цвет из гамма-пространства (того, как значение хранится в файле/памяти) в линейное
vec3 gamma_to_linear(const vec3& gamma_value)
{
    return vec3{
            std::pow(gamma_value.r, GAMMA),
            std::pow(gamma_value.g, GAMMA),
            std::pow(gamma_value.b, GAMMA)
        };
}

vec3 linear_to_gamma(const vec3& linear_value)
{
    return vec3{
            std::pow(linear_value.r, 1.0f / GAMMA),
            std::pow(linear_value.g, 1.0f / GAMMA),
            std::pow(linear_value.b, 1.0f / GAMMA)
        };
}

struct Sampler
{
    unsigned char *image;
    int width, height;
    int colors;

    Sampler(unsigned char *img, int x, int y, int c) : image(img), width(x), height(y), colors(c) {}

    vec3 pixel(int x, int y)
    {
        vec3 result;
        result.r = image[(y * width * colors) + (x * colors)];
        result.g = image[(y * width * colors) + (x * colors) + 1];
        result.b = image[(y * width * colors) + (x * colors) + 2];
        return result;
    }

    /// Линейно интерполирует значения между a и b, параметр интерполяции - t
    vec3 lerp(const vec3& a, const vec3& b, float t)
    {
        return a * (1 - t) + b * t;
    }

    /// Возвращаем цвет точки с координатами (x, y) [координаты x, y - нормированные, в диапазоне 0.0..1.0]
    vec3 at(float x, float y, bool linear = false)
    {
        float x_full = std::max(x * (width), 0.0f);
        float y_full = std::max(y * (height), 0.0f);

        int x0 = x_full; // Отсекаем дробную часть
        int y0 = y_full;

        int x1 = std::min(x0 + 1, width);
        int y1 = std::min(y0 + 1, height);

        float dx = x_full - x0;
        float dy = y_full - y0;

        // +-----+-----+
        // |     |     |
        // | v0  | v1  |
        // +-----+-----+
        // |     |     |
        // | v2  | v3  |
        // +-----+-----+
        //
        // v0 (x0, y0)
        // v1 (x1, y0)
        // v2 (x0, y1)
        // v3 (x1, y1)
        // color = lerp(lerp(v0, v1, dx), lerp(v2, v3, dx), dy)
        vec3 v0 = gamma_to_linear(pixel(x0, y0));
        vec3 v1 = gamma_to_linear(pixel(x1, y0));
        vec3 v2 = gamma_to_linear(pixel(x0, y1));
        vec3 v3 = gamma_to_linear(pixel(x1, y1));

        vec3 result = lerp(
            lerp(v0, v1, dx),
            lerp(v2, v3, dx),
            dy
        );
        if (linear)
        {
           return result;
        }
        return linear_to_gamma(result);
    }
};

struct LinearSampler
{
    vec3 *image;
    int width, height;

    LinearSampler(vec3 *img, int x, int y) : image(img), width(x), height(y) {}

    vec3 pixel(int x, int y)
    {
        return image[(y * width) + x];
    }

    /// Линейно интерполирует значения между a и b, параметр интерполяции - t
    vec3 lerp(const vec3& a, const vec3& b, float t)
    {
        return a * (1 - t) + b * t;
    }

    /// Возвращаем цвет точки с координатами (x, y) [координаты x, y - нормированные, в диапазоне 0.0..1.0]
    vec3 at(float x, float y)
    {
        float x_full = std::max(x * (width), 0.0f);
        float y_full = std::max(y * (height), 0.0f);

        int x0 = x_full; // Отсекаем дробную часть
        int y0 = y_full;

        int x1 = std::min(x0 + 1, width);
        int y1 = std::min(y0 + 1, height);

        float dx = x_full - x0;
        float dy = y_full - y0;

        // +-----+-----+
        // |     |     |
        // | v0  | v1  |
        // +-----+-----+
        // |     |     |
        // | v2  | v3  |
        // +-----+-----+
        //
        // v0 (x0, y0)
        // v1 (x1, y0)
        // v2 (x0, y1)
        // v3 (x1, y1)
        // color = lerp(lerp(v0, v1, dx), lerp(v2, v3, dx), dy)
        vec3 v0 = pixel(x0, y0);
        vec3 v1 = pixel(x1, y0);
        vec3 v2 = pixel(x0, y1);
        vec3 v3 = pixel(x1, y1);

        vec3 result = lerp(
            lerp(v0, v1, dx),
            lerp(v2, v3, dx),
            dy
        );
        return result;
    }
};

