#pragma once

#include <cstdint>
#include <vector>
#include "Math/Math.h"
#include "Raytracer/Framebuffer.h"
#include "Raytracer/Camera.h"
#include "Raytracer/Primitives.h"

struct Light
{
    Math::Vector position;
    Math::Vector color;
    float radius = 0.f;
    float intensity = 0.f;
    float exp = 2.f;
};

struct Material
{
    Math::Vector diffuseColor;
    Math::Vector specularColor;
    float specularExp = 0.f;
    float specularIntensity = 0.f;
};

struct Scene
{
    Math::Vector backgroundColor;
    Math::Vector ambientLight;

    // These objects are referenced because they could be managed in different places.
    std::vector<std::shared_ptr<const Primitive>> primitives;
    std::vector<std::shared_ptr<const Light>> lights;
};

class Raytracer
{
public:
    Raytracer();

    // Add a material and returns its id.
    int AddMaterial(const std::shared_ptr<const Material>);

    // Render scene.
    void Render(const Scene&, const Camera&, Framebuffer&) const;

private:
    Math::Vector Raycast(const Math::Ray&, const Scene&, const float drawDistance) const;
    Math::Vector Shade(const RaycastSample& sample, const Math::Vector& camera, const Light&, const Material&) const;

    std::vector<std::shared_ptr<const Material>> materials;
};