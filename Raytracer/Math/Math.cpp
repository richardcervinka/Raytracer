#include "Math.h"

float Math::IntersectTriangle(const Ray& ray, const Vector& p0, const Vector& p1, const Vector& p2)
{
    // Möller–Trumbore intersection algorithm.
    // Source: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    const float e = 0.0000001f;

    const Vector edge1 = p1 - p0;
    const Vector edge2 = p2 - p0;

    const Vector h = Vector::Cross(ray.direction, edge2);
    const Vector s = ray.origin - p0;
    const Vector q = Vector::Cross(s, edge1);

    const float a = edge1 * h;
    if (a < e && a > -e)
    {
        return INFINITY;
    }

    const float f = 1.0f / a;
    const float u = f * (s * h);
    if (u < 0.0f || u > 1.0f)
    {
        return INFINITY;
    }
    
    const float v = f * (ray.direction * q);
    if (v < 0.0f || u + v > 1.0f)
    {
        return INFINITY;
    }

    // At this stage we can compute t to find out where the intersection point is on the line.
    const float t = f * (edge2 * q);

    // This means that there is a line intersection but not a ray intersection.
    if (t <= e)
    {
        return INFINITY;
    }

    return t;
}

float Math::IntersectSphere(const Ray& ray, const Vector& position, const float radius)
{
    // Geometric Solution.
    // Source: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    
    const float radius2 = radius * radius;
    const Vector L = position - ray.origin;
    const float tca = L * ray.direction;
    if (tca < 0.0f)
    {
        return INFINITY;
    }
    const float d2 = L * L - tca * tca;
    if (d2 > radius2)
    {
        return INFINITY;
    }
    const float thc = sqrtf(radius2 - d2);
    float t0 = tca - thc;
    float t1 = tca + thc;

    if (t0 > t1)
    {
        std::swap(t0, t1);
    }
    if (t0 < 0.0f)
    {
        // If t0 is negative, let's use t1 instead.
        t0 = t1;

        // Both t are negative.
        if (t0 < 0.0f)
        {
            return INFINITY;
        }
    }
    return t0;
}