
#pragma once
#include "scene.hpp"

#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

class FirstMaterials : public Scene {
public:
    FirstMaterials()
    {

        auto material_ground = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
        auto material_center = std::make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
        auto material_left = std::make_shared<Metal>(Color(0.8f, 0.8f, 0.8f));
        auto material_right = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f));

        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, material_center));
        m_world.Add(std::make_shared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
        m_world.Add(std::make_shared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, material_right));

        m_camera.spec.position.z = 0.00001f;
        m_camera.spec.image_width = 400;
        m_camera.spec.samples_per_pixel = 40;
        m_camera.spec.max_bounces = 20;
        m_camera.Bake();
    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }
};
