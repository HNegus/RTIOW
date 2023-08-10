#include "image.hpp"

#include <iostream>

Image::Image(uint32_t width, uint32_t height)
    : width(width), height(height)
{
    m_pixels.resize(height);
    for (auto& row: m_pixels) {
        row.resize(width);
    }
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

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            std::cout << m_pixels[i][j] << " ";
        }
        std::cout << std::endl;
    }
}