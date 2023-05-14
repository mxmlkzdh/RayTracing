#pragma once
#include <memory>
#include "world.hpp"
#include "xy_rectangle.hpp"
#include "xz_rectangle.hpp"
#include "yz_rectangle.hpp"
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class Cube : public Object {
public:
    Point min;
    Point max;
    std::shared_ptr<Material> material;
private:
    World sides;
public:
    Cube(const Point& min, const Point& max, const std::shared_ptr<Material> material) : min(min), max(max), material(material) {
        sides.add(std::make_shared<XYRectangle>(min.x, max.x, min.y, max.y, max.z, material));
        sides.add(std::make_shared<XYRectangle>(min.x, max.x, min.y, max.y, min.z, material));
        sides.add(std::make_shared<XZRectangle>(min.x, max.x, min.z, max.z, max.y, material));
        sides.add(std::make_shared<XZRectangle>(min.x, max.x, min.z, max.z, min.y, material));
        sides.add(std::make_shared<YZRectangle>(min.y, max.y, min.z, max.z, max.x, material));
        sides.add(std::make_shared<YZRectangle>(min.y, max.y, min.z, max.z, min.x, material));
    }
    bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        return sides.hit(ray, min, max, record);
    };
    bool boundingBox(const double, const double, AABB& outputBox) const override {
        outputBox = AABB(min, max);
        return true;
    }
};

}