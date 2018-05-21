#pragma once

#include "Raytracer/Raytracer.h"

class Sample
{
public:
    Sample();
    void Draw(Framebuffer& output);

private:
    Scene scene;
    Camera camera;
    Raytracer raytracer;
};