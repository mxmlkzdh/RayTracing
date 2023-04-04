#pragma once
#include <vector>
#include <memory>
#include "hittable.hpp"

namespace RayTracing {

class HittableList: public Hittable {
private:
    std::vector<std::shared_ptr<Hittable>> objects;
public:
    HittableList() = default;
    HittableList(const std::shared_ptr<Hittable> object) {
        add(object);
    };
    void add(const std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        HitRecord tempRecord;
        bool hitAnything = false;
        double maxSoFar = max;
        for (const std::shared_ptr<Hittable>& object : objects) {
            if (object->hit(ray, min, maxSoFar, tempRecord)) {
                hitAnything = true;
                maxSoFar = tempRecord.t;
                record = tempRecord;
            }
        }
        return hitAnything;
    }
};

}