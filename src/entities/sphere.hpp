#pragma once

#include "entity.hpp"
#include <memory>
#include "materials/material.hpp"

class Sphere : public Entity {

public:
    Sphere(Point3 center, real_type radius, std::shared_ptr<Material> material)
        : m_center{center},
        m_radius{radius},
        m_material{material}
    {};
    bool ClosestHit(const Ray& ray, Interval interval, HitRecord& record) const override;

private:
    Point3 m_center;
    real_type m_radius;

    std::shared_ptr<Material> m_material;
};