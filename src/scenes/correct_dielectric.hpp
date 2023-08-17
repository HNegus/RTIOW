
#pragma once
#include "scene.hpp"

#include "materials/lambertian.hpp"
#include "materials/metal.hpp"
#include "materials/dielectric.hpp"

class CorrectDielectric : public Scene {
public:
    CorrectDielectric()
    {

        auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
        auto material_left = std::make_shared<Dielectric>(1.5);
        auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

        m_world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
        m_world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));
        // m_world.Add(std::make_shared<Sphere>(Point3(-2.5, 0.0, -1.0), 0.5, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(-2.0, 0.0, -0.9), -0.5, material_left));

        m_camera.spec.position = Vec3(-0.5, 0.0, 0.5);
        m_camera.spec.lookat = Vec3(-0.5, 0.0, 0.0);
        m_camera.spec.vfov = 90;

        m_camera.spec.image_width = 4096;
        m_camera.spec.samples_per_pixel = 100;
        m_camera.spec.max_bounces = 50;
        m_camera.Bake();
    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }
};
