#pragma once
#include <vector>
#include <memory>
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class World: public Object {
private:
    std::vector<std::shared_ptr<Object>> objects;
public:
    World() = default;
    virtual ~World() {}
    void add(const std::shared_ptr<Object>& object) {
        objects.push_back(object);
    }
    void clear() {
        objects.clear();
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        bool hitAnything = false;
        double maxSoFar = max;
        HitRecord tempRecord;
        for (const auto& object : objects) {
            if (object->hit(ray, min, maxSoFar, tempRecord)) {
                maxSoFar = tempRecord.time;
                record = tempRecord;
                hitAnything = true;
            }
        }
        return hitAnything;
    };
};

}