#include <iostream>

#include "base/image.hpp"

#include "utils/debug.hpp"

#include "entities/sphere.hpp"

#include "entities/entity_list.hpp"

#include "base/camera.hpp"

#include "materials/lambertian.hpp"
#include "materials/material.hpp"
#include "materials/metal.hpp"

#include "scenes/first_sphere.hpp"
#include "scenes/first_materials.hpp"
#include "scenes/first_fov.hpp"
#include "scenes/first_free_cam.hpp"
#include "scenes/first_fuzz.hpp"
#include "scenes/first_dielectric.hpp"
#include "scenes/correct_dielectric.hpp"
#include "scenes/first_dof.hpp"
#include "scenes/book1_final.hpp"
#include "scenes/first_moving.hpp"

int main(int, char**)
{
    /* Book 1 */
    // FirstSphere scene;
    // FirstMaterials scene;
    // FirstFOV scene;
    // FirstFreeCam scene;
    // FirstFuzz scene;
    // FirstDielectric scene;
    // CorrectDielectric scene;
    // FirstDOF scene;
    // Book1Final scene;

    /* Book 2 */
    FirstMoving scene;

    scene.Show();
}
