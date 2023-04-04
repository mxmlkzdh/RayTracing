#pragma once
#include "hittable.hpp"

namespace RayTracing {

class Sphere: public Hittable {
public:
    Point3D center;
    double radius;
public:
    Sphere(const Point3D& center, const double radius): center(center), radius(radius) {};
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        Vector3D oc = ray.origin - center;
        const double a = dot(ray.direction, ray.direction);
        const double b = 2 * dot(ray.direction, oc);
        const double c = dot(oc, oc) - radius * radius;
        const double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return false;
        }
        // Find the nearest root that lies in the acceptable range.
        double root = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (root < min || max < root) {
            root = (-b + std::sqrt(discriminant)) / (2.0 * a);
            if (root < min || max < root) {
                return false;
            }
        }
        // Update the HitRecord
        record.t = root;
        record.point = ray.at(record.t);
        record.normal = (record.point - center) / radius;
        return true;
    }
};

}