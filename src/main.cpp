#include <string>
#include <thread>
#include "util.hpp"
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "engine.hpp"
#include "renderer/linear.hpp"
#include "renderer/parallel.hpp"

int main(int, char const**) {

    // Automatically benchmarks the execution of this code block (main) in seconds.
    RayTracing::Util::Timer timer;

    // Image
    const std::string DEFAULT_OUTPUT_FILE_PATH = "data/output.ppm";
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;
    const RayTracing::Image image(DEFAULT_OUTPUT_FILE_PATH, IMAGE_WIDTH, ASPECT_RATIO);

    // Scene
    const RayTracing::Scene scene;

    // Camera
    const RayTracing::Point LOOK_FROM(0, 0, 1.5);
    const RayTracing::Point LOOK_AT(0, 0, -1.35);
    const RayTracing::Vector3 V_UP(0, 1, 0);
    const double V_FOV = 45.0;
    const RayTracing::Camera camera(LOOK_FROM, LOOK_AT, V_UP, V_FOV, ASPECT_RATIO);

    // Render
    const RayTracing::Engine engine(image, scene, camera);
    engine.render();

    return EXIT_SUCCESS;

}
