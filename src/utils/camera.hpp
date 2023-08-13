#pragma once

#include "common.hpp"

#include "entities/entity_list.hpp"
#include "color.hpp"
#include "image.hpp"

struct CameraSpec {
    real_type aspect_ratio = 0;
    real_type focal_length = 0;

    uint32_t image_width = 0, image_height = 0;

    Vec3 center{};
};

class Camera {
public:

    CameraSpec spec;

    Camera(const CameraSpec& specification);
    Camera() : Camera(CameraSpec{}) {};

    void Render(const EntityList& world);

private:
    struct CameraDetails {
        real_type viewport_width = 0, viewport_height = 0;
        Vec3 pixel_dx = 0, pixel_dy = 0;
        Vec3 viewport_x {}, viewport_y {};
        Vec3 viewport_upper_left {}, pixel00_loc {};
    };

    CameraDetails m_details;
    Image m_image;

    Color RayColor(const Ray& ray, const EntityList& world);
};