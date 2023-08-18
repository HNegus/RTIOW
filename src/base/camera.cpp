#include "camera.hpp"

#include "materials/material.hpp"

#include <algorithm>
#include <functional>
#include <atomic>
#include <execution>
#include <numeric>

void Camera::Bake()
{
    // Setup image
    // TODO: add ability to set either image width/height on Camera creation,
    // or set aspect ratio and calculate the width/height
    spec.image_height = static_cast<int>(spec.image_width / spec.aspect_ratio);
    spec.image_height = spec.image_height < 1 ? 1 : spec.image_height;

    // spec.focal_length = (spec.position - spec.lookat).Length();

    m_image.width = spec.image_width;
    m_image.height = spec.image_height;
    m_image.samples_per_pixel = spec.samples_per_pixel;
    m_image.Resize();

    real_type h = static_cast<real_type>(tan(DegToRad(spec.vfov)/2));
    m_details.viewport_height = 2.0f * h * spec.focus_dist;
    m_details.viewport_width = m_details.viewport_height;
    m_details.viewport_width *= (static_cast<real_type>(spec.image_width) / spec.image_height);

    m_details.w = (spec.position - spec.lookat).Unit();
    m_details.u = spec.up.Cross(m_details.w).Unit();
    m_details.v = m_details.w.Cross(m_details.u);

    m_details.viewport_x = m_details.viewport_width * m_details.u;
    m_details.viewport_y = m_details.viewport_height * -m_details.v;

    m_details.pixel_dx = m_details.viewport_x / spec.image_width;
    m_details.pixel_dy = m_details.viewport_y / spec.image_height;

    m_details.viewport_upper_left = spec.position - (spec.focus_dist * m_details.w)
        - m_details.viewport_x / 2 - m_details.viewport_y / 2;
    m_details.pixel00_loc = m_details.viewport_upper_left
        + 0.5 * (m_details.pixel_dx + m_details.pixel_dy);

    real_type defocus_radius = spec.focus_dist * static_cast<real_type>(tan(DegToRad(spec.defocus_angle / 2)));
    m_details.defocus_disk_u = m_details.u * defocus_radius;
    m_details.defocus_disk_v = m_details.v * defocus_radius;
    return;
}

void Camera::Render(const EntityList& world)
{
    // TODO: clean
#define THREADS
#ifndef THREADS
    for (uint32_t j = 0; j < spec.image_height; j++) {
        std::clog << "Scanlines remaining: " << spec.image_height - j << std::endl;
        for (uint32_t i = 0; i < spec.image_width; i++) {
            for (uint32_t s = 0; s < spec.samples_per_pixel; s++) {
                Ray ray = GetRay(i, j);
                m_image[j][i] += RayColor(ray, world, spec.max_bounces);
            }
        }
    }
#else
    std::vector<int> rowidx(m_image.height - 1);
    std::iota(rowidx.begin(), rowidx.end(), 1);
    std::atomic<int> done{0};

    std::for_each(std::execution::par, rowidx.begin(), rowidx.end(), [&](int j) {
        std::clog << "Scanlines remaining: " << spec.image_height - done.fetch_add(1) << std::endl;
        for (uint32_t i = 0; i < spec.image_width; i++) {
            for (uint32_t s = 0; s < spec.samples_per_pixel; s++) {
                Ray ray = GetRay(i, j);
                m_image[j][i] += RayColor(ray, world, spec.max_bounces);
            }
        }
    });
#endif
    m_image.ToPPM();
}

Ray Camera::GetRay(uint32_t i, uint32_t j) const
{
    Vec3 pixel_center = m_details.pixel00_loc
                        + (i * m_details.pixel_dx)
                        + (j * m_details.pixel_dy);
    Vec3 sample_vector = pixel_center + GetSample();
    Vec3 ray_origin = (spec.defocus_angle <= 0) ? spec.position : DefocusDiskSample();
    Vec3 ray_direction = sample_vector - ray_origin;
    return Ray(ray_origin, ray_direction);
}

Vec3 Camera::GetSample() const
{
    real_type px = -0.5f + RandomReal();
    real_type py = -0.5f + RandomReal();
    return (px * m_details.pixel_dx) + (py * m_details.pixel_dy);
}

Point3 Camera::DefocusDiskSample() const
{
    Point3 p = Vec3::RandomInUnitDisk();
    return spec.position + (p.x * m_details.defocus_disk_u) + (p.y * m_details.defocus_disk_v);
}

Color Camera::RayColor(Ray ray, const EntityList& world, uint32_t depth)
{


    Color final_color(1.0);
    Color attenuation{};
    HitRecord record {};
    Interval interval(0.001f, infinity);
    Ray scattered{};

    // Max_bounces reached.
    if (depth == 0) {
        return final_color;
    }

    while (depth > 0) {
        depth -= 1;

        if (world.ClosestHit(ray, interval, record)) {
            if (record.material->Scatter(ray, record, attenuation, scattered)) {
                final_color *= attenuation;
                ray = scattered;
                continue;
            }
            return Color(0.0f);
        }

        // Return sky color
        Vec3 unit = ray.direction.Unit();
        real_type a = 0.5f * (unit.y + 1.0f);

        Color sky_color = (1.0f - a) * Color(1.0f) + a * Color(0.5f, 0.7f, 1.0f);
        return final_color * sky_color;
    }
    return final_color;
}

Vec3 Camera::SimpleDiffuseDirection(const HitRecord& record) const
{
    return Vec3::RandomOnHemisphere(record.normal);
}

Vec3 Camera::LambertianDiffuseDirection(const HitRecord& record) const
{
    return record.normal + Vec3::RandomUnit();;
}
