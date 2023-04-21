#pragma once
#include <memory>
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"
#include "../constants.hpp"

namespace RayTracing {

class XZRectangle: public Object {
public:
    double x0;
    double x1;
    double z0;
    double z1;
    double y;
    std::shared_ptr<Material> material;
public:
    XZRectangle(const double x0, const double x1, const double z0, const double z1, const double y, const std::shared_ptr<Material> material)
        : x0(x0), x1(x1), z0(z0), z1(z1), y(y), material(material) {
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        const double t = (y - ray.origin.y) / ray.direction.y;
        if (t < min || t > max) {
            return false;
        }
        const double x = ray.origin.x + (t * ray.direction.x);
        const double z = ray.origin.z + (t * ray.direction.z);
        if (x < x0 || x > x1 || z < z0 || z > z1) {
            return false;
        }
        record.time = t;
        record.point = ray.at(t);
        record.u = (x - x0) / (x1 - x0);
        record.v = (z - z0) / (z1 - z0);
        record.material = material;
        record.setNormal(ray, UnitVector(0, 1, 0));
        return true;
    };
    virtual bool boundingBox(const double, const double, AABB& outputBox) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Y dimension a small amount.
        outputBox = AABB(Point(x0, y - Constants::AABB_PADDING, z0), Point(x1, y + Constants::AABB_PADDING, z1));
        return true;
    }
};

}