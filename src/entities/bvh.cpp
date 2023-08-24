#include "bvh.hpp"

#include <algorithm>

BVH_Node::BVH_Node(const std::vector<std::shared_ptr<Entity>>& list,
    uint32_t start, uint32_t end)
{
    bounding_box = AABB::empty;

    for (uint32_t i = start; i < end; i++) {
        bounding_box = AABB(bounding_box, list[i]->bounding_box);
    }

    int axis = bounding_box.LongestAxis();
    auto comparator = axis == 0 ? xCompare : axis == 1 ? yCompare : zCompare;
    uint32_t range = end - start;

    if (range == 1) {
        left = list[start];
        right = left;
    } else if (range == 2) {

        if (comparator(list[start], list[start + 1])) {
            left = list[start];
            right = list[start + 1];
        } else {
            left = list[start + 1];
            right = list[start];
        }
    } else {
        std::vector<std::shared_ptr<Entity>> sorted = list;
        std::sort(sorted.begin() + start, sorted.begin() + end, comparator);
        uint32_t middle = start + range/2;
        left = std::make_shared<BVH_Node>(sorted, start, middle);
        right = std::make_shared<BVH_Node>(sorted, middle, end);
    }
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