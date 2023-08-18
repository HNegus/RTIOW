#include "entity_list.hpp"

bool EntityList::ClosestHit(const Ray& ray, Interval interval, HitRecord& record) const
{
    HitRecord tmp_rec{};
    bool hit = false;

    record.t = interval.max;

    for (const std::shared_ptr<Entity>& entity: m_entities) {
        if (entity->ClosestHit(ray, Interval(interval.min, record.t), tmp_rec)) {
            hit = true;
            record = tmp_rec;
        }
    }

    return hit;
}