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
        Point minimum(Constants::DOUBLE_INFINITY, Constants::DOUBLE_INFINITY, Constants::DOUBLE_INFINITY);
        Point maximum(-Constants::DOUBLE_INFINITY, -Constants::DOUBLE_INFINITY, -Constants::DOUBLE_INFINITY);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    const double x = i * box.maximum.x + (1 - i) * box.minimum.x;
                    const double y = j * box.maximum.y + (1 - j) * box.minimum.y;
                    const double z = k * box.maximum.z + (1 - k) * box.minimum.z;
                    const double newx = cosTheta * x + sinTheta * z;
                    const double newz = -sinTheta * x + cosTheta * z;
                    Vector3 tester(newx, y, newz);
                    for (int c = 0; c < 3; c++) {
                        minimum[c] = std::fmin(minimum[c], tester[c]);
                        maximum[c] = std::fmax(maximum[c], tester[c]);
                    }
                }
            }
        }
        box = AABB(minimum, maximum);
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        Vector3 origin = ray.origin;
        Vector3 direction = ray.direction;
        origin[0] = cosTheta * ray.origin[0] - sinTheta * ray.origin[2];
        origin[2] = sinTheta * ray.origin[0] + cosTheta * ray.origin[2];
        direction[0] = cosTheta * ray.direction[0] - sinTheta * ray.direction[2];
        direction[2] = sinTheta * ray.direction[0] + cosTheta * ray.direction[2];
        Ray rotatedRay(origin, direction, ray.time);
        if (!object->hit(rotatedRay, min, max, record)) {
            return false;
        }
        Point point = record.point;
        Vector3 normal = record.normal;
        point[0] = cosTheta * record.point[0] + sinTheta * record.point[2];
        point[2] = -sinTheta * record.point[0] + cosTheta * record.point[2];
        normal[0] = cosTheta * record.normal[0] + sinTheta * record.normal[2];
        normal[2] = -sinTheta * record.normal[0] + cosTheta * record.normal[2];
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