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

class Cube: public Object {
public:
    Point minimum;
    Point maximum;
    std::shared_ptr<Material> material;
private:
    World sides;
public:
    Cube(const Point& minimum, const Point& maximum, const std::shared_ptr<Material> material): minimum(minimum), maximum(maximum), material(material) {
        sides.add(std::make_shared<XYRectangle>(minimum.x, maximum.x, minimum.y, maximum.y, maximum.z, material));
        sides.add(std::make_shared<XYRectangle>(minimum.x, maximum.x, minimum.y, maximum.y, minimum.z, material));
        sides.add(std::make_shared<XZRectangle>(minimum.x, maximum.x, minimum.z, maximum.z, maximum.y, material));
        sides.add(std::make_shared<XZRectangle>(minimum.x, maximum.x, minimum.z, maximum.z, minimum.y, material));
        sides.add(std::make_shared<YZRectangle>(minimum.y, maximum.y, minimum.z, maximum.z, maximum.x, material));
        sides.add(std::make_shared<YZRectangle>(minimum.y, maximum.y, minimum.z, maximum.z, minimum.x, material));
    }
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        return sides.hit(ray, min, max, record);
    };
    virtual bool boundingBox(const double, const double, AABB& outputBox) const override {
        outputBox = AABB(minimum, maximum);
        return true;
    }
};

}