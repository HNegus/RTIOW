#pragma once

#include "entity.hpp"
#include <memory>
#include "materials/material.hpp"

class Sphere : public Entity {

public:
    Sphere() = delete;
    Sphere(const Point3& center, real_type radius, std::shared_ptr<Material> material)
        : m_center{center},
        m_radius{radius},
        m_material{material}
    {
        Vec3 radius_v(radius, radius, radius);
        bounding_box = AABB(center - radius_v, center + radius_v);
    }
    virtual bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override;
    inline const AABB& BoundingBox() const override { return bounding_box; }

protected:
    mutable Point3 m_center;
    real_type m_radius;

    std::shared_ptr<Material> m_material;
};

class MovingSphere : public Sphere {

public:
    MovingSphere(const Point3& origin_center, const Point3& dest_center,
                 real_type radius, std::shared_ptr<Material> material)
        : Sphere(origin_center, radius, material)
        , m_center_displacement{dest_center - origin_center}
        , m_original_center{origin_center}
        {
            Vec3 radius_v(radius, radius, radius);
            AABB end_position_bbox(dest_center - radius_v, dest_center + radius_v);
            // NOTE: possible because bounding_box is set in parent constructor
            bounding_box = AABB(bounding_box, end_position_bbox);
        }
    bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override;
    inline const AABB& BoundingBox() const override { return bounding_box; }

protected:
    Vec3 m_center_displacement{};
    Vec3 m_original_center{};
};