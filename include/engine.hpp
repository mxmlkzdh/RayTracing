#pragma once
#include "camera.hpp"
#include "scene.hpp"
#include "image.hpp"
#include "renderer.hpp"
#include "render/linear.hpp"

namespace RayTracing {

class Engine {
public:
    Image image;
    Scene scene;
    Camera camera;
    int samplesPerPixel;
    int maxDepth;
public:
    Engine(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel = 10, const int maxDepth = 50):
        image(image), scene(scene), camera(camera), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {
    }
    void render(const Renderer& renderer = LinearRenderer()) const {
        renderer.render(image, scene, camera, samplesPerPixel, maxDepth);
    }
};

}