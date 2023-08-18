
#pragma once
#include "scene.hpp"

#include "materials/dielectric.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

class Book1Final : public Scene {
public:
    Book1Final()
    {

        BuildWorld();

        auto& cam = m_camera.spec;

        cam.image_width = 1200;
        cam.samples_per_pixel = 500;
        cam.max_bounces = 50;

        cam.vfov = 20;
        cam.position = Point3(13.0f, 2.0f, 3.0f);
        cam.lookat = Point3(0.0f, 0.0f, 0.0f);

        cam.defocus_angle = 0.6f;
        cam.focus_dist = 10.0f;

        m_camera.Bake();
    }

    void BuildWorld()
    {
        std::shared_ptr<Material> ground_material = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000, ground_material));

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                real_type choose_mat = RandomReal();
                Point3 center(a + 0.9f * RandomReal(), 0.2f, b + 0.9f * RandomReal());

                if ((center - Point3(4.0f, 0.2f, 0.0f)).Length() > 0.9f) {
                    std::shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        Color albedo = Vec3::Random() * Vec3::Random();
                        sphere_material = std::make_shared<Lambertian>(albedo);
                        m_world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    } else if (choose_mat < 0.95) {
                        // metal
                        Color albedo = Vec3::Random(0.5, 1);
                        real_type fuzz = RandomNumber(0, 0.5);
                        sphere_material = std::make_shared<Metal>(albedo, fuzz);
                        m_world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    } else {
                        // glass
                        sphere_material = std::make_shared<Dielectric>(1.5);
                        m_world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
        m_world.Add(std::make_shared<Sphere>(Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

        std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
        m_world.Add(std::make_shared<Sphere>(Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

        std::shared_ptr<Material> material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
        m_world.Add(std::make_shared<Sphere>(Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));
    }

    void Show() override
    {
        m_camera.SetGammaCorrection(true);
        m_camera.Render(m_world);
    }
};
