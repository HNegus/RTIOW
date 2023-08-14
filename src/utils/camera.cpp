#include "camera.hpp"

void Camera::Bake()
{
    // Setup image
    // TODO: add ability to set either image width/height on Camera creation,
    // or set aspect ratio and calculate the width/height
    spec.image_height = static_cast<int>(spec.image_width / spec.aspect_ratio);
    spec.image_height = spec.image_height < 1 ? 1 : spec.image_height;

    image.width = spec.image_width;
    image.height = spec.image_height;
    image.samples_per_pixel = spec.samples_per_pixel;
    image.Resize();

    m_details.viewport_height = 2.0;
    m_details.viewport_width = m_details.viewport_height;
    m_details.viewport_width *= (static_cast<real_type>(spec.image_width) / spec.image_height);

    m_details.viewport_x = Vec3(m_details.viewport_width, 0, 0);
    m_details.viewport_y = Vec3(0, -m_details.viewport_height, 0);

    m_details.pixel_dx = m_details.viewport_x / spec.image_width;
    m_details.pixel_dy = m_details.viewport_y / spec.image_height;

    m_details.viewport_upper_left = spec.center - Vec3(0, 0, spec.focal_length)
        - m_details.viewport_x / 2 - m_details.viewport_y / 2;
    m_details.pixel00_loc = m_details.viewport_upper_left
        + 0.5 * (m_details.pixel_dx + m_details.pixel_dy);
}

void Camera::Render(const EntityList& world)
{
    for (size_t i = 0; i < spec.image_width; i++) {
        std::clog << "Scanlines remaining: " << spec.image_width - i << std::endl;
        for (size_t j = 0; j < spec.image_height; j++) {
            for (uint32_t s = 0; s < spec.samples_per_pixel; s++) {
                Ray ray = GetRay(i, j);
                image[j][i] += RayColor(ray, world, spec.max_bounces);
            }
        }
    }

    image.ToPPM();
}

Ray Camera::GetRay(int i, int j) const
{
    Vec3 pixel_center = m_details.pixel00_loc
                        + (i * m_details.pixel_dx)
                        + (j * m_details.pixel_dy);
    Vec3 sample_vector = pixel_center + GetSample();
    Vec3 ray_direction = sample_vector - spec.center;
    return Ray(spec.center, ray_direction);
}

Vec3 Camera::GetSample() const
{
    real_type px = -0.5 + RandomReal();
    real_type py = -0.5 + RandomReal();
    return (px * m_details.pixel_dx) + (py * m_details.pixel_dy);
}

Color Camera::RayColor(const Ray& ray, const EntityList& world, uint32_t depth)
{
    // Max_bounces reached.
    if (depth <= 0) {
        return Color(0);
    }

    HitRecord record {};
    Interval interval(0.001, infinity);
    if (world.Hit(ray, interval, record)) {
        Vec3 bounce_direction = LambertianDiffuseDirection(record);
        return 0.5 * RayColor(Ray(record.position, bounce_direction), world, depth-1);
    }

    Vec3 unit = ray.direction.Unit();

    real_type a = 0.5f * (unit.y + 1.0f);
    return (1.0f - a) * Color(1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}

Vec3 Camera::SimpleDiffuseDirection(const HitRecord& record) const
{
    return Vec3::RandomOnHemisphere(record.normal);
}

Vec3 Camera::LambertianDiffuseDirection(const HitRecord& record) const
{
    return record.normal + Vec3::RandomUnit();;
}
