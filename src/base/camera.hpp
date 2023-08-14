#pragma once

#include "utils/common.hpp"

#include "entities/entity_list.hpp"
#include "utils/color.hpp"
#include "image.hpp"

struct CameraSpec {
    real_type aspect_ratio = 16 / 9.0;
    real_type focal_length = 1.0;

    uint32_t image_width = 400, image_height = 0;
    uint32_t samples_per_pixel = 10;
    uint32_t max_bounces = 10;

    Vec3 center{};
};

class Camera {
public:

    CameraSpec spec;

    Camera(const CameraSpec& specification) : spec{specification}
    {
        Bake();
    };
    Camera() : Camera(CameraSpec{}) {};


    inline void SetGammaCorrection(bool b) { m_image.gamma_correction_enabled = b; }
    void Render(const EntityList& world);
    void Bake();

private:
    Image m_image;

    struct CameraDetails {
        real_type viewport_width = 0, viewport_height = 0;
        Vec3 pixel_dx = 0, pixel_dy = 0;
        Vec3 viewport_x {}, viewport_y {};
        Vec3 viewport_upper_left {}, pixel00_loc {};
    };

    CameraDetails m_details;

    Ray GetRay(int i, int j) const;
    Vec3 GetSample() const;
    Color RayColor(const Ray& ray, const EntityList& world, uint32_t depth);

    Vec3 SimpleDiffuseDirection(const HitRecord& record) const;
    Vec3 LambertianDiffuseDirection(const HitRecord& record) const;



};