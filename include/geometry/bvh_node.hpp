#pragma once
#include <vector>
#include <memory>
#include <vector>
#include <algorithm>
#include "world.hpp"
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class BVHNode: public Object {
private:
    std::shared_ptr<Object> left;
    std::shared_ptr<Object> right;
    AABB box;
public:
    BVHNode() {}
    BVHNode(const World& world, const double initTime, const double finalTime):
        BVHNode(world.objects, 0, world.objects.size(), initTime, finalTime) {
    }
    BVHNode(std::vector<std::shared_ptr<Object>>& srcObjects,
        const std::size_t start, const std::size_t end, const double initTime, const double finalTime) {
        std::vector<std::shared_ptr<Object>> objects = srcObjects; // Create a modifiable array of the source scene objects.
        int axis = Util::random(0, 2);
        auto comparator = (axis == 0) ? boxXCompare : (axis == 1) ? boxYCompare : boxZCompare;
        std::size_t objectSpan = end - start;

        if (objectSpan == 1) {
            left = right = objects[start];
        } else if (objectSpan == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                left = objects[start];
                right = objects[start + 1];
            } else {
                left = objects[start + 1];
                right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);
            std::size_t mid = start + objectSpan / 2;
            left = std::make_shared<BVHNode>(objects, start, mid, initTime, finalTime);
            right = std::make_shared<BVHNode>(objects, mid, end, initTime, finalTime);
        }
        AABB boxLeft;
        AABB boxRight;
        if (!left->bounding_box(time0, finalTime, boxLeft) || !right->bounding_box(initTime, finalTime, boxRight)) {
            std::cerr << "No bounding box in BVHNode constructor.\n";
        }
        box = surrounding_box(boxLeft, boxRight);
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        if (!box.hit(ray, min, max)) {
            return false;
        }
        bool hitLeft = left->hit(ray, min, max, rec);
        bool hitRight = right->hit(ray, min, hitLeft ? record.time : max, record);
        return hitLeft || hitRight;
    };
    virtual bool boundingBox(const double initTime, const double finalTime, AABB& outputBox) const override {
        outputBox = box;
        return true;
    }
private:
    bool boxXCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return boxCompare(a, b, 0);
    }

    bool boxYCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return boxCompare(a, b, 1);
    }

    bool boxZCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return boxCompare(a, b, 2);
    }
    bool boxCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b, const int axis) const {
        AABB boxA;
        AABB boxB;
        if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB)) {
            std::cerr << "No bounding box in BVHNode constructor.\n";
        }
        return boxA.minimum[axis] < boxB.minimum[axis];
    }

};

}