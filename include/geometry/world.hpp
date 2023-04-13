#pragma once
#include <vector>
#include <memory>
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class World: public Object {
private:
    std::vector<std::shared_ptr<Object>> objects;
public:
    World() {}
    void add(const std::shared_ptr<Object> object) {
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
    virtual bool boundingBox(const double initTime, const double finalTime, AABB& outputBox) const override {
        if (objects.empty()) {
            return false;
        }
        AABB tempBox;
        bool firstBox = true;
        for (const auto& object : objects) {
            if (!object->boundingBox(initTime, finalTime, tempBox)) {
                return false;
            }
            outputBox = firstBox ? tempBox : surroundingBox(outputBox, tempBox);
            firstBox = false;
        }
        return true;
    }
};

}