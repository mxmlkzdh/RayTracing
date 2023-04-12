#pragma once
#include <memory>
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class MovingSphere: public Object {
public:
    Point initCenter;
    Point finalCenter;
    double radius;
    double initTime;
    double finalTime;
    std::shared_ptr<Material> material;
public:
    MovingSphere(const Point& initCenter, const Point& finalCenter, const double radius, const double initTime, const double finalTime, std::shared_ptr<Material> material)
        : initCenter(initCenter), finalCenter(finalCenter), radius(radius), initTime(initTime), finalTime(finalTime), material(material) {
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        const Vector3 oc = ray.origin - center(ray.time);
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
        record.material = material;
        record.time = root;
        record.point = ray.at(record.time);
        Vector3 outwardNormal = (record.point - center(ray.time)) / radius;
        record.setNormal(ray, outwardNormal);
        getSphereUV(outwardNormal, record.u, record.v);
        return true;
    };
private:
    Point center(const double time) const {
        return initCenter + ((time - initTime) / (finalTime - initTime)) * (finalCenter - initCenter);
    }
    void getSphereUV(const Vector3& outwardNormal, double& u, double& v) const {
        const double theta = std::acos(-outwardNormal.y);
        const double phi = std::atan2(-outwardNormal.z, outwardNormal.x) + Constants::PI;
        u = phi / (2.0 * Constants::PI);
        v = theta / Constants::PI;
    }
};

}