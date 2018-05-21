#pragma once

#include <cstdint>
#include <vector>
#include <Math/Math.h>

enum class FramebufferFormat
{
    RGBA8,
    BGRA8
};

class Framebuffer
{
public:
    const FramebufferFormat format;

    Framebuffer(const FramebufferFormat);

    // If arguments are invalid, does nothing.
    void Resize(const int width, const int height);

    // Out of range pixels are ignored.
    void SetPixel(const int x, const int y, const Math::Vector& color);

    int Width() const { return width; }
    int Height() const { return height; }

    // Get raw data pointer.
    const uint8_t* const Data() { return data.data(); }

private:
    int width;
    int height;
    std::vector<uint8_t> data;
};