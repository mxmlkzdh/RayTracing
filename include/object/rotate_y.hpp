#pragma once
#include <memory>
#include <cmath>
#include "../util.hpp"
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class RotateY: public Object {
public:
    std::shared_ptr<Object> object;
    double angle;
private:
    double sinTheta;
    double cosTheta;
    bool hasBox;
    AABB box;
public:
    RotateY(const std::shared_ptr<Object> object, const double angle): object(object), angle(angle) {
        const double radians = Util::degreesToRadians(angle);
        sinTheta = std::sin(radians);
        cosTheta = std::cos(radians);
        hasBox = object->boundingBox(0, 1, box);
        Point min(Constants::DOUBLE_INFINITY, Constants::DOUBLE_INFINITY, Constants::DOUBLE_INFINITY);
        Point max(-Constants::DOUBLE_INFINITY, -Constants::DOUBLE_INFINITY, -Constants::DOUBLE_INFINITY);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    const double x = i * box.max.x + (1 - i) * box.min.x;
                    const double y = j * box.max.y + (1 - j) * box.min.y;
                    const double z = k * box.max.z + (1 - k) * box.min.z;
                    const double newx = cosTheta * x + sinTheta * z;
                    const double newz = -sinTheta * x + cosTheta * z;
                    Vector3 tester(newx, y, newz);
                    for (std::size_t c = 0; c < 3; c++) {
                        min[c] = std::fmin(min[c], tester[c]);
                        max[c] = std::fmax(max[c], tester[c]);
                    }
                }
            }
        }
        box = AABB(min, max);
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        Vector3 origin = ray.origin;
        Vector3 direction = ray.direction;
        origin.x = cosTheta * ray.origin.x - sinTheta * ray.origin.z;
        origin.z = sinTheta * ray.origin.x + cosTheta * ray.origin.z;
        direction.x = cosTheta * ray.direction.x - sinTheta * ray.direction.z;
        direction.z = sinTheta * ray.direction.x + cosTheta * ray.direction.z;
        Ray rotatedRay(origin, direction, ray.time);
        if (!object->hit(rotatedRay, min, max, record)) {
            return false;
        }
        Point point = record.point;
        Vector3 normal = record.normal;
        point.x = cosTheta * record.point.x + sinTheta * record.point.z;
        point.z = -sinTheta * record.point.x + cosTheta * record.point.z;
        normal.x = cosTheta * record.normal.x + sinTheta * record.normal.z;
        normal.z = -sinTheta * record.normal.x + cosTheta * record.normal.z;
        record.point = point;
        record.setNormal(rotatedRay, normal);
        return true;
    };
    virtual bool boundingBox(const double, const double, AABB& outputBox) const override {
        outputBox = box;
        return hasBox;
    }
};

}