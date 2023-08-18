#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"

class EntityList : public Entity {

public:

    EntityList() = default;

    inline void Add(std::shared_ptr<Entity> entity) { m_entities.push_back(entity); }
    inline void Clear() { m_entities.clear(); }

    bool ClosestHit(const Ray& ray, Interval interval, HitRecord& record) const override;

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};