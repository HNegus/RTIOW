#include <iostream>

#include "utils/image.hpp"

#include "utils/ray.hpp"

int main(int, char**){

    Image image(256, 256);
    for (size_t i = 0; i < image.height; i++) {
        std::clog << "Scanlines remaining: " << image.height - i << std::endl;
        for (size_t j = 0; j < image.width; j++) {
            image[i][j] = {j / 255.0f, i / 255.0f, 0.0f};
        }
    }
    image.ToPPM();
}
