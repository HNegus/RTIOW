#pragma once

#include "entity.hpp"

class Sphere : public Entity {

public:
    Sphere(Point3 center, real_type radius) : m_center{center}, m_radius{radius} {};
    bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override;

private:
    Point3 m_center;
    real_type m_radius;

};