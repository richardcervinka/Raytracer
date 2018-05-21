#include "Framebuffer.h"

Framebuffer::Framebuffer(const FramebufferFormat format_):
    format{format_}, width{0}, height{0}
{}

void Framebuffer::Resize(const int width, const int height)
{
    if (this->width == width && this->height == height)
    {
        return;
    }
    if (width < 0 || height < 0)
    {
        return;
    }
    this->width = width;
    this->height = height;
    data.resize(width * width * 4);
}

void Framebuffer::SetPixel(const int x, const int y, const Math::Vector& color)
{
    // Out of range arguments.
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return;
    }

    // BGRA
    if (format == FramebufferFormat::BGRA8)
    {
        const int offset = 4 * (x + y * width);
        data[offset + 0] = Math::Unorm(color.z); // B
        data[offset + 1] = Math::Unorm(color.y); // G
        data[offset + 2] = Math::Unorm(color.x); // R
        data[offset + 3] = Math::Unorm(color.w); // A
        return;
    }
    
    // RGBA
    if (format == FramebufferFormat::RGBA8)
    {
        const int offset = 4 * (x + y * width);
        data[offset + 0] = Math::Unorm(color.x); // R
        data[offset + 1] = Math::Unorm(color.y); // G
        data[offset + 2] = Math::Unorm(color.z); // B
        data[offset + 3] = Math::Unorm(color.w); // A
        return;
    }
}