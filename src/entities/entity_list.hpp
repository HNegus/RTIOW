#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"

class BVH_Node;

class EntityList : public Entity {
    friend BVH_Node;

public:
    EntityList() = default;
    EntityList(const std::shared_ptr<Entity> entity) {
        Add(entity);
    }

    inline void Add(std::shared_ptr<Entity> entity)
    {
        m_entities.push_back(entity);
        bounding_box = AABB(bounding_box, entity->bounding_box);
    }
    inline void Clear() { m_entities.clear(); }

    bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override;
    inline const AABB& BoundingBox() const override { return bounding_box; }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};