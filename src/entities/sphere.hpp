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
    {};
    virtual bool ClosestHit(const Ray& ray, Interval interval, HitRecord& record) const override;

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
        {}
    bool ClosestHit(const Ray& ray, Interval interval, HitRecord& record) const override;

protected:
    Vec3 m_center_displacement{};
    Vec3 m_original_center{};
};