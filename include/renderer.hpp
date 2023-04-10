#pragma once
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"

namespace RayTracing {

class Renderer {
public:
    virtual void render(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) const = 0;
    virtual ~Renderer() {}
};

}