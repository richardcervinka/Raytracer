#include "Raytracer.h"

Raytracer::Raytracer()
{
    // Create default material.
    auto material = std::make_shared<Material>();
    material->diffuseColor = {0.9f, 0.9f, 0.9f, 0.0f};
    material->specularColor = {1.0f, 1.0f, 1.0f, 0.0f};
    material->specularExp = 0.f;
    material->specularIntensity = 0.f;
    AddMaterial(material);
}

int Raytracer::AddMaterial(const std::shared_ptr<const Material> material)
{
    materials.push_back(material);
    return static_cast<int>(materials.size() - 1);
}

void Raytracer::Render(const Scene& scene, const Camera& camera, Framebuffer& framebuffer) const
{
    const int width = framebuffer.Width();
    const int height = framebuffer.Height();

    // Invalid framebuffer dimensions.
    if (width == 0 || height == 0)
    {
        return;
    }

    // Projection axes scale.
    const float sy = std::tanf(camera.VFov() / 2.f);
    const float sx = std::tanf(camera.HFov() / 2.f);

    const auto look = camera.Look();
    const auto up = camera.Up() * sy;
    const auto left = Math::Vector::Cross(camera.Look(), camera.Up()) * sx;

    // Apply transformations.
    for (auto primitive : scene.primitives)
    {
        primitive->Transform();
    }

    // For each vertical pixels.
    for (int y = 0; y < height; ++y)
    {
        // For each horizontal pixels.
        for (int x = 0; x < width; ++x)
        {
            // Screen-space to normal-space (-1;1)
            const float ny = 2.f * (0.5f - (y + 0.5f) / height);
            const float nx = 2.f * (0.5f - (x + 0.5f) / width);
            
            // Ray from cam position to far-plane intersection point.
            const Math::Ray ray(camera.position, look + up * ny + left * nx);

            // Compte pixel color.
            const auto color = Raycast(ray, scene, camera.drawDistance);

            // Store result to framebuffer.
            framebuffer.SetPixel(x, y, color);
        }
    }
}

Math::Vector Raytracer::Raycast(const Math::Ray& ray, const Scene& scene, const float drawDistance) const
{
    float distance = drawDistance;

    RaycastSample sample;
    RaycastSample finalSample;
    int materialId = 0;

    for (const auto& primitive : scene.primitives)
    {
        if (primitive == nullptr)
        {
            continue;
        }

        const float t = primitive->Raycast(ray, distance, sample);

        // No intersection.
        if (t == INFINITY)
        {
            continue;
        }

        distance = t;
        finalSample = sample;
        materialId = primitive->materialId;
    }

    // No intersection, use background color and skip shading.
    if (distance >= drawDistance)
    {
        return scene.backgroundColor;
    }

    // If materialId is invalid, use default material.
    if (materialId < 0 || materialId >= static_cast<int>(materials.size()))
    {
        materialId = 0;
    }

    const auto material = materials[materialId];

    // Final color initialized to ambient lighting result.
    Math::Vector color = Math::Vector::Mul(material->diffuseColor, scene.ambientLight);

    // Shading.
    for (const auto& light : scene.lights)
    {
        color += Shade(finalSample, ray.origin, *light, *material);
    }
    return color;
}

Math::Vector Raytracer::Shade(const RaycastSample& sample, const Math::Vector& camera, const Light& light, const Material& material) const
{
    if (light.radius <= 0.f)
    {
        return Math::Vector();
    }

    // View vector (from intersection point to camera).
    const auto v = Math::Vector::Normalized(camera - sample.position);

    // Light vector (from intersection point to light).
    const auto l = Math::Vector::Normalized(light.position - sample.position);

    // Half vector.
    const auto half = Math::Vector::Normalized(v + l);

    // Distance from light.
    const float lightDistance = Math::Vector::Distance(sample.position, light.position);

    const float cos = sample.normal * l;

    // Backface lighting.
    if (cos < 0.f)
    {
        return Math::Vector();
    }

    // Point is out of light range.
    if (lightDistance >= light.radius)
    {
        return Math::Vector();
    }

    // Inverse-Square falloff.
    // float falloff *= light.intensity / (lightDistance * lightDistance + 0.00001f);

    // Exponential falloff.
    const float falloff = light.intensity * std::powf(1.f - lightDistance / light.radius, light.exp);

    const Math::Vector diffuse = Math::Vector::Mul(material.diffuseColor, light.color * (falloff * cos));

    // Specular.
    const float specularIntensity = std::powf(std::max(sample.normal * half, 0.f), material.specularExp) * (material.specularIntensity * falloff);
    const Math::Vector specular = Math::Vector::Mul(light.color, material.specularColor) * specularIntensity;

    // Final color composition.
    return diffuse + specular;
}