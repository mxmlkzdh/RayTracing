#pragma once
#include "object.hpp"
#include "vector3.hpp"

namespace RayTracing {

class Sphere: public Object {
public:
    Point center;
    double radius;
public:
    Sphere(const Point& center, const double radius): center(center), radius(radius) {}
    virtual ~Sphere() {}
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        const Vector3 oc = ray.origin - center;
        const double a = RayTracing::dot(ray.direction, ray.direction);
        const double b = 2 * RayTracing::dot(ray.direction, oc);
        const double c = RayTracing::dot(oc, oc) - radius * radius;
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
        record.time = root;
        record.point = ray.at(record.time);
        record.setNormal(ray, (record.point - center) / radius);
        return true;
    };
};

}