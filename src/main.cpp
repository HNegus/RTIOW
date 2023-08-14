#include <iostream>

#include "base/image.hpp"

#include "utils/debug.hpp"

#include "entities/sphere.hpp"

#include "entities/entity_list.hpp"

#include "base/camera.hpp"

#include "materials/lambertian.hpp"
#include "materials/material.hpp"
#include "materials/metal.hpp"

#include "scenes/first_sphere.hpp"
#include "scenes/first_materials.hpp"
#include "scenes/scene.hpp"

int main(int, char**)
{

    // CameraSpec camera_spec = { .aspect_ratio = 16.0 / 9.0,
    //     .focal_length = 1.0,
    //     .image_width = 400,
    //     .samples_per_pixel = 50,
    //     .max_bounces = 10,
    //     };
    // std::cout <<
    FirstMaterials scene;
    scene.Show();
}
