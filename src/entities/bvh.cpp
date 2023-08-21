#include "bvh.hpp"

#include <algorithm>

BVH_Node::BVH_Node(const std::vector<std::shared_ptr<Entity>>& list,
    uint32_t start, uint32_t end)
{
    int axis = RandomInt(0, 2);
    auto comparator = axis == 0 ? xCompare : axis == 1 ? yCompare : zCompare;

    std::vector<std::shared_ptr<Entity>> entities = list;

    uint32_t range = end - start;

    if (range == 1) {
        left = entities[start];
        right = left;
    } else if (range == 2) {

        if (comparator(entities[start], entities[start + 1])) {
            left = entities[start];
            right = entities[start + 1];
        } else {
            left = entities[start + 1];
            right = entities[start];
        }
    } else {
        std::sort(entities.begin() + start, entities.begin() + end, comparator);
        uint32_t middle = start + range/2;
        left = std::make_shared<BVH_Node>(list, start, middle);
        right = std::make_shared<BVH_Node>(list, middle, end);
    }
    bounding_box = AABB(left->bounding_box, right->bounding_box);

}

bool BVH_Node::Hit(const Ray& ray, Interval interval, HitRecord& record) const
{
    if (!bounding_box.Hit(ray, interval)) {
        return false;
    }

    bool hit_left = left->Hit(ray, interval, record);
    interval.max = hit_left ? record.t : interval.max;
    bool hit_right = right->Hit(ray, interval, record);

    return hit_left || hit_right;
}