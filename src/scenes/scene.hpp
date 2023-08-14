#pragma once

#include "base/camera.hpp"
#include "entities/entity_list.hpp"

class Scene {

public:
    virtual ~Scene() = default;

    virtual void Show() = 0;

protected:
    Camera m_camera;
    EntityList m_world;
};