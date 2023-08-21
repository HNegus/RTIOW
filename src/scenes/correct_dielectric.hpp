
#pragma once
#include "scene.hpp"

#include "entities/sphere.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"
#include "materials/dielectric.hpp"

class CorrectDielectric : public Scene {
public:
    CorrectDielectric()
    {

        auto material_ground = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
        auto material_center = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
        auto material_left = std::make_shared<Dielectric>(1.5f);
        auto material_right = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 0.0f);

        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, material_center));
        m_world.Add(std::make_shared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, material_right));
        // m_world.Add(std::make_shared<Sphere>(Point3(-2.5f, 0.0f, -1.0f), 0.5f, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(-2.0f, 0.0f, -0.9f), -0.5f, material_left));

        m_camera.spec.position = Vec3(-0.5f, 0.0f, 0.5f);
        m_camera.spec.lookat = Vec3(-0.5f, 0.0f, 0.0f);
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
