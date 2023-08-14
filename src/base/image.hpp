#pragma once

#include <cstdint>
#include <vector>
#include "utils/color.hpp"

class Image {

public:
    uint32_t width = 0, height = 0;
    uint32_t samples_per_pixel = 1;
    bool gamma_correction_enabled = false;

    Image() = default;
    Image(uint32_t width, uint32_t height);
    std::vector<Color>& operator[](int index);

    void ToPPM();
    void Resize();

private:
    std::vector<std::vector<Color>> m_pixels;
    inline Color GammaCorrect(Color c) const
    {
        return sqrt(c);
    }

};

