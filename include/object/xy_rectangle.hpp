#pragma once
#include <memory>
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"
#include "../constants.hpp"

namespace RayTracing {

class XYRectangle : public Object {
public:
    double x0;
    double x1;
    double y0;
    double y1;
    double z;
    std::shared_ptr<Material> material;
public:
    XYRectangle(const double x0, const double x1, const double y0, const double y1, const double z, const std::shared_ptr<Material> material)
        : x0(x0), x1(x1), y0(y0), y1(y1), z(z), material(material) {
    }
    bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        const double t = (z - ray.origin.z) / ray.direction.z;
        if (t < min || t > max) {
            return false;
        }
        const double x = ray.origin.x + (t * ray.direction.x);
        const double y = ray.origin.y + (t * ray.direction.y);
        if (x < x0 || x > x1 || y < y0 || y > y1) {
            return false;
        }
        record.time = t;
        record.point = ray.at(t);
        record.u = (x - x0) / (x1 - x0);
        record.v = (y - y0) / (y1 - y0);
        record.material = material;
        record.setNormal(ray, Vector3(0, 0, 1));
        return true;
    };
    bool boundingBox(const double, const double, AABB& outputBox) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Z dimension a small amount.
        outputBox = AABB(Point(x0, y0, z - Constants::AABB_PADDING), Point(x1, y1, z + Constants::AABB_PADDING));
        return true;
    }
};

}