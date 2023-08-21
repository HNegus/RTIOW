#include "sphere.hpp"

bool Sphere::Hit(const Ray& ray, Interval interval, HitRecord& record) const
{
    Vec3 camera_position = ray.origin - m_center;

    real_type a = ray.direction.Dot(ray.direction);
    real_type half_b = ray.direction.Dot(camera_position);
    real_type c = camera_position.Dot(camera_position) - m_radius * m_radius;

    real_type D = half_b * half_b - a * c;

    if (D < 0) {
        return false;
    }

    real_type sqrtD = std::sqrt(D);
    real_type root = (-half_b - sqrtD) / a;

    if (!interval.Surrounds(root)) {
        root = (-half_b + sqrtD) / a;
        if (!interval.Surrounds(root)) {
            return false;
        }
    }

    record.t = root;
    record.position = ray.At(root);

    // Make sure that normal always faces outward.
    Vec3 normal = (record.position - m_center) / m_radius;
    record.SetFaceNormal(ray, normal);

    record.material = m_material;

    return true;
}

bool MovingSphere::Hit(const Ray& ray, Interval interval, HitRecord& record) const
{
    m_center = m_original_center + ray.time*m_center_displacement;
    return Sphere::Hit(ray, interval, record);
}
