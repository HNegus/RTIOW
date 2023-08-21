
#pragma once
#include "scene.hpp"

#include "entities/sphere.hpp"
#include "materials/lambertian.hpp"

class FirstSphere : public Scene {
public:
    FirstSphere()
    {
        std::shared_ptr<Material> material = std::make_shared<Diffuse>(0.5f);

        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, material));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, material));

        m_camera.spec.position = Vec3(0.0f, 0.0f, 0.0001f);
        m_camera.spec.image_width = 800;
        m_camera.Bake();
    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }

};
