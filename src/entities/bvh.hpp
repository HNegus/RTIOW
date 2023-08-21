#pragma once

#include "entity_list.hpp"


class BVH_Node : public Entity {

public:
    BVH_Node(const std::vector<std::shared_ptr<Entity>>& list, uint32_t start, uint32_t end);
    BVH_Node(const EntityList& list)
        : BVH_Node(list.m_entities, 0, list.m_entities.size())
    {}

    bool Hit(const Ray& ray, Interval interval,
        HitRecord& record) const override;
    inline const AABB& BoundingBox() const override { return bounding_box; }

private:
    std::shared_ptr<Entity> left = nullptr, right = nullptr;

    static bool Compare(const std::shared_ptr<Entity> a,
                        const std::shared_ptr<Entity> b,
                        uint32_t index)
    {
        return a->bounding_box[index].min < b->bounding_box[index].min;
    }
    static bool xCompare(const std::shared_ptr<Entity> a,
                         const std::shared_ptr<Entity> b)
    {
        return Compare(a, b, 0);
    }
    static bool yCompare(const std::shared_ptr<Entity> a,
                         const std::shared_ptr<Entity> b)
    {
        return Compare(a, b, 1);
    }
    static bool zCompare(const std::shared_ptr<Entity> a,
                         const std::shared_ptr<Entity> b)
    {
        return Compare(a, b, 2);
    }

};