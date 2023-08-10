#pragma once

#include <cstdint>
#include <vector>
#include "color.hpp"

class Image {

public:
    uint32_t width = 0, height = 0;

    Image(uint32_t width, uint32_t height);
    std::vector<Color>& operator[](int index);


    void ToPPM();

private:
    std::vector<std::vector<Color>> m_pixels;
};