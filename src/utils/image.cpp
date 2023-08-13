#include "image.hpp"

#include <iostream>
#include "utils/interval.hpp"

Image::Image(uint32_t width, uint32_t height)
    : width(width), height(height)
{
    Resize();
}

std::vector<Color> &Image::operator[](int index)
{
    return m_pixels[index];
}

void Image::ToPPM()
{
    std::cout << "P3" << std::endl;
    std::cout << width << " " << height << std::endl;
    std::cout << 255 << std::endl;

    Interval intensity(0.0, 0.999999);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Color c = intensity.Clamp(m_pixels[i][j] / samples_per_pixel);
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

void Image::Resize()
{
    m_pixels.resize(height);
    for (auto& row : m_pixels) {
        row.resize(width);
    }
}