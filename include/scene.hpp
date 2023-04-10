#pragma once
#include <memory>
#include "geometry/world.hpp"
#include "geometry/sphere.hpp"
#include "material/lambertian.hpp"
#include "material/metal.hpp"
#include "material/dielectric.hpp"
#include "texture/image_texture.hpp"
#include "texture/checker_texture.hpp"

namespace RayTracing {

class Scene {
public:
    World world;
public:
    Scene() {
        auto earthTexture = std::make_shared<RayTracing::ImageTexture>("data/earthmap.jpg");
        auto earthSurface = std::make_shared<RayTracing::Lambertian>(earthTexture);
        auto checkerGround = std::make_shared<RayTracing::CheckerTexture>(RayTracing::Color(0.01, 0.01, 0.01), RayTracing::Color(0.99, 0.99, 0.99));
        auto materialGround = std::make_shared<RayTracing::Lambertian>(checkerGround);
        auto materialCenter = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(0.0, 0.1, 0.3));
        auto materialLeft = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.75, 0.0, 0.0));
        auto materialRight = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.75, 0.5, 0.25));
        auto materialFront = std::make_shared<RayTracing::Dielectric>(1.5);
        auto materialFrontFront = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(10.0 / 256, 35.0 / 256, 10.0 / 256));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, -100.5, -1), 100, materialGround));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, 0, -1.35), 0.5, earthSurface));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(-1.0, 0.0, -1), 0.5, materialLeft));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0.825, -0.1, -0.65), 0.4, materialRight));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(-0.25, -0.25, -0.25), 0.25, materialFront));
        world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0.25, -0.4, -0.5), 0.1, materialFrontFront));
    }
};

}