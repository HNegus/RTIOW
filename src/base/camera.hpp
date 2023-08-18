#pragma once

#include "utils/common.hpp"

#include "entities/entity_list.hpp"
#include "utils/color.hpp"
#include "image.hpp"

struct CameraSpec {
    real_type aspect_ratio = 16 / 9.0f;
    real_type focal_length = 1.0;
    real_type vfov = 90.0;

    uint32_t image_width = 400, image_height = 0;
    uint32_t samples_per_pixel = 10;
    uint32_t max_bounces = 10;

    Point3 position = Point3(0.0, 0.0, 1.0);
    Point3 lookat = Point3(0.0);
    Vec3 up = Vec3(0.0, 1.0, 0.0);

    real_type defocus_angle = 0;
    real_type focus_dist = 10;
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
        Vec3 u{}, v{}, w{};
        Vec3 defocus_disk_u{}, defocus_disk_v{};
    };

    CameraDetails m_details;

    Ray GetRay(uint32_t i, uint32_t j) const;
    Vec3 GetSample() const;
    Point3 DefocusDiskSample() const;
    Color RayColor(const Ray& ray, const EntityList& world, uint32_t depth);

    Vec3 SimpleDiffuseDirection(const HitRecord& record) const;
    Vec3 LambertianDiffuseDirection(const HitRecord& record) const;



};