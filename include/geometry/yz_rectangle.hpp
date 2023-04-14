#pragma once
#include <memory>
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class YZRectangle: public Object {
public:
    double y0;
    double y1;
    double z0;
    double z1;
    double k;
    std::shared_ptr<Material> material;
public:
    YZRectangle(const double y0, const double y1, const double z0, const double z1, const double k, const std::shared_ptr<Material> material)
        : y0(y0), y1(y1), z0(z0), z1(z1), k(k), material(material) {
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        const double t = (k - ray.origin.x) / ray.direction.x;
        if (t < min || t > max) {
            return false;
        }
        const double y = ray.origin.y + (t * ray.direction.y);
        const double z = ray.origin.z + (t * ray.direction.z);
        if (y < y0 || y > y1 || z < z0 || z > z1) {
            return false;
        }
        record.time = t;
        record.point = ray.at(t);
        record.u = (y - y0) / (y1 - y0);
        record.v = (z - z0) / (z1 - z0);
        record.material = material;
        record.setNormal(ray, Vector3(1, 0, 0));
        return true;
    };
    virtual bool boundingBox(const double, const double, AABB& outputBox) const override {
        // The bounding box must have non-zero width in each dimension, so pad the X dimension a small amount.
        outputBox = AABB(Point(k - 0.0001, y0, z0), Point(k + 0.0001, y1, z1));
        return true;
    }
};

}