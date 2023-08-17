
#pragma once
#include "scene.hpp"

#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

class FirstFreeCam : public Scene {
public:
    FirstFreeCam()
    {

        auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
        auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
        auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

        m_world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
        m_world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.4, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

        m_camera.spec.image_width = 400;
        m_camera.spec.samples_per_pixel = 10;
        m_camera.spec.max_bounces = 10;

        m_camera.spec.vfov = 90;
        m_camera.spec.position = Point3(-2, 2, 1);
        m_camera.spec.lookat = Point3(0, 0, -1);
        m_camera.spec.up = Point3(0, 1, 0);

        m_camera.Bake();

    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }
};