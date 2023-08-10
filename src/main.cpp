#include <iostream>

#include "utils/image.hpp"

#include "utils/ray.hpp"

#include "utils/debug.hpp"

Color RayColor(const Ray& ray)
{
    Vec3 unit = ray.direction.Unit();

    real_type a = 0.5f*(unit.y + 1.0f);
    return (1.0f-a)*Color(1.0f) + a*Color(0.0f, 0.0f, 1.0f);
}

int main(int, char**)
{
    auto aspect_ratio = 16.0f / 9.0f;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Viewport widths less than one are ok since they are real valued.
    auto focal_length = 1.0f;
    auto viewport_height = 2.0f;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = Point3(0, 0, 0);

    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center
                             - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    Image image(image_width, image_height);
    for (size_t j = 0; j < image.height; j++) {
        std::clog << "Scanlines remaining: " << image.height - j << std::endl;
        for (size_t i = 0; i < image.width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);
            image[j][i] = RayColor(r);
        }
    }
    image.ToPPM();
}
