
#pragma once
#include "scene.hpp"

#include "materials/lambertian.hpp"

class FirstSphere : public Scene {
public:
    FirstSphere()
    {
        std::shared_ptr<Material> material = std::make_shared<Diffuse>(0.5);

        m_world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material));
        m_world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, material));

        m_camera.spec.image_width = 800;
        m_camera.Bake();
    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }

};
