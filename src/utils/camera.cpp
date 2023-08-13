#include "camera.hpp"

Camera::Camera(const CameraSpec& specification)
    : spec{specification}
{

    // Setup image
    // TODO: add ability to set either image width/height on Camera creation,
    // or set aspect ratio and calculate the width/height
    spec.image_height = static_cast<int>(spec.image_width / spec.aspect_ratio);
    spec.image_height = spec.image_height < 1 ? 1 : spec.image_height;

    m_image = Image(spec.image_width, spec.image_height);

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
        for (size_t j = 0; j < spec.image_height; j++) {
            Vec3 pixel_center = m_details.pixel00_loc
                                + (i * m_details.pixel_dx)
                                + (j * m_details.pixel_dy);
            Vec3 ray_direction = pixel_center - spec.center;
            Ray ray(spec.center, ray_direction);
            m_image[j][i] = RayColor(ray, world);
        }
    }

    m_image.ToPPM();
}

Color Camera::RayColor(const Ray& ray, const EntityList& world)
{
    HitRecord record {};
    Interval interval(0, infinity);
    if (world.Hit(ray, interval, record)) {
        return 0.5 * (record.normal + Color(1));
    }

    Vec3 unit = ray.direction.Unit();

    real_type a = 0.5f * (unit.y + 1.0f);
    return (1.0f - a) * Color(1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}