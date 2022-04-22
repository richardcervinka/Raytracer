#include "Sample.h"

Sample::Sample()
{
    // Box material.
    auto boxMaterial = std::make_shared<Material>();
    boxMaterial->diffuseColor = {0.9f, 0.6f, 0.2f, 1.0f};
    boxMaterial->specularColor = {1.0f, 1.0f, 1.0f, 1.0f};
    boxMaterial->specularExp = 200.0f;
    boxMaterial->specularIntensity = 1.0f;
    const auto boxMid = raytracer.AddMaterial(boxMaterial);

    // Sphere material.
    auto sphereMaterial = std::make_shared<Material>();
    sphereMaterial->diffuseColor = {1.0f, 1.0f, 1.0f, 1.0f};
    sphereMaterial->specularColor = {1.0f, 1.0f, 1.0f, 1.0f};
    sphereMaterial->specularExp = 200.f;
    sphereMaterial->specularIntensity = 0.6f;
    const auto sphereMid = raytracer.AddMaterial(sphereMaterial);

    // Plane material.
    auto planeMaterial = std::make_shared<Material>();
    planeMaterial->diffuseColor = {0.5f, 0.5f, 0.5f, 1.0f};
    planeMaterial->specularColor = {1.0f, 1.0f, 1.0f, 1.0f};
    planeMaterial->specularExp = 30.f;
    planeMaterial->specularIntensity = 0.5f;
    const auto planeMid = raytracer.AddMaterial(planeMaterial);

    // Box vertices.
    const Math::Vector vertices[] =
    {
        {-100.f, -100.f, -100.f, 0.f},
        {-100.f,  100.f, -100.f, 0.f},
        { 100.f,  100.f, -100.f, 0.f},
        { 100.f, -100.f, -100.f, 0.f},
        {-100.f, -100.f,  100.f, 0.f},
        {-100.f,  100.f,  100.f, 0.f},
        { 100.f,  100.f,  100.f, 0.f},
        { 100.f, -100.f,  100.f, 0.f}
    };

    const int indices[][3] =
    {
        {0, 1, 3},
        {3, 1, 2},
        {1, 5, 6},
        {1, 6, 2},
        {3, 2, 6},
        {3, 6, 7},
        {5, 1, 0},
        {5, 1, 0},
        {5, 0, 4},
        {5, 4, 7},
        {5, 7, 6}
    };

    // Create triangles.
    for (const auto ti : indices)
    {
        auto triangle = std::make_shared<Triangle>();
        triangle->v0 = vertices[ti[0]];
        triangle->v1 = vertices[ti[1]];
        triangle->v2 = vertices[ti[2]];
        triangle->materialId = boxMid;
        scene.primitives.push_back(triangle);
    }

    // Plane.
    auto plane = std::make_shared<Plane>();
    plane->position = {0.f, -100.f, 0.f, 0.f};
    plane->materialId = planeMid;
    scene.primitives.push_back(plane);

    //Sphere.
    auto sphere = std::make_shared<Sphere>();
    sphere->radius = 130.f;
    sphere->materialId = sphereMid;
    scene.primitives.push_back(sphere);

    // Front light.
    auto frontLight = std::make_shared<Light>();
    frontLight->position = {100.f, 500.f, -550.f, 0.f};
    frontLight->color = {1.f, 1.f, 1.f, 0.f};
    frontLight->radius = 3000.f;
    frontLight->intensity = 3.f;
    frontLight->exp = 6.f;
    scene.lights.push_back(frontLight);

    // Back light.
    auto backLight = std::make_shared<Light>();
    backLight->position = {0.f, 500.f, 300.f, 0.f};
    backLight->color = {175.f / 255.f, 226.f / 255.f, 255.f / 255.f, 0.f};
    backLight->radius = 1500.f;
    backLight->intensity = 3.f;
    backLight->exp = 4.f;
    scene.lights.push_back(backLight);

    // Ambient light.
    scene.ambientLight = {4.f / 255.f, 12.f / 255.f, 21.f / 255.f, 0.f};

    // Camera.
    camera.drawDistance = 10000.f;
    camera.position = {225.f, 190.f, -225.f, 0.f};
    camera.LookAtTarget({0.f, -20.f, 0.f, 0.f});
}

void Sample::Draw(Framebuffer& output)
{
    camera.SetAspectRatio(static_cast<float>(output.Width()), static_cast<float>(output.Height()));
    raytracer.Render(scene, camera, output);
}
