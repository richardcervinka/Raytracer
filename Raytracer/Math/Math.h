#pragma once

#include <cmath>
#include <complex>

// Column vectors.
// Row major matrix.

// Math constants.
namespace Math
{
    const float Pi = 3.1415926535898f;
    const float Pi2 = Pi * 2.f;
    const float PiHalf = Pi / 2.f;
}

#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"
#include "Plane.h"

namespace Math
{
    // Linear interpolation.
    inline float Interpolate(const float from, const float to, const float ratio)
    {
        return from + (to - from) * ratio;
    }

    // Linear interpolation.
    inline Vector Interpolate(const Vector& from, const Vector& to, const float ratio)
    {
        return Vector(
            from.x + (to.x - from.x) * ratio,
            from.y + (to.y - from.y) * ratio,
            from.z + (to.z - from.z) * ratio,
            from.w + (to.w - from.w) * ratio
        );
    }

    template <typename T>
    inline T Clamp(const T value, const T min, const T max)
    {
        if (value <= min)
        {
            return min;
        }
        if (value >= max)
        {
            return max;
        }
        return value;
    }

    template <typename T>
    inline bool Range(const T value, const T min, const T max)
    {
        return (value >= min) && (value <= max);
    }

    // Value in range float (0.0; 1.0) to uint8_t (0, 255).
    inline uint8_t Unorm(const float value)
    {
        return static_cast<uint8_t>(Math::Clamp(value * 255.f, 0.f, 255.f));
    }

    inline float IntersectPlane(const Ray& ray, const Plane& plane)
    {
        const float r = plane * ray.direction;
        if (r == 0.f)
        {
            return INFINITY;
        }
        return -(plane * Math::Vector(ray.origin.x, ray.origin.y, ray.origin.z, 1.f)) / r;
    }

    float IntersectTriangle(const Ray& ray, const Vector& p0, const Vector& p1, const Vector& p2);
    float IntersectSphere(const Ray& ray, const Vector& position, const float radius);
}