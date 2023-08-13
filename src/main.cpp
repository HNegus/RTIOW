#include <iostream>

#include "utils/image.hpp"

#include "utils/ray.hpp"

#include "utils/debug.hpp"

#include "entities/sphere.hpp"

#include "entities/entity_list.hpp"

#include "utils/interval.hpp"

#include "utils/camera.hpp"

int main(int, char**)
{

    CameraSpec camera_spec = { .aspect_ratio = 16.0 / 9.0,
        .focal_length = 1.0,
        .image_width = 1080,
        .samples_per_pixel = 100,
        .max_bounces = 50,
        };

    Camera camera(camera_spec);
    EntityList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    camera.Render(world);
}
