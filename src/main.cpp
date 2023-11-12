#include <argh/argh.h>
#include <string>
#include <thread>
#include "util.hpp"
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "engine.hpp"
#include "render/linear.hpp"
#include "render/parallel.hpp"

int main(int argc, char const* argv[]) {

    // Automatically benchmarks the execution of this code block (main) in seconds.
    RayTracing::Util::Timer timer;

    // Command Line Processing
    auto cmdl = argh::parser(argc, argv);

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    std::string fileName;
    cmdl("o", "data/output.ppm") >> fileName;
    int width;
    cmdl("w", 400) >> width;
    const RayTracing::Image image(fileName, width, ASPECT_RATIO);

    // Scene
    const RayTracing::Scene scene(RayTracing::Color(0.0, 0.0, 0.0));

    // Camera
    const RayTracing::Point LOOK_FROM(0.0, 0.0, 1.5);
    const RayTracing::Point LOOK_AT(0.0, 0.0, -1.35);
    const RayTracing::Vector3 V_UP(0.0, 1.0, 0.0);
    const double V_FOV = 45.0;
    const RayTracing::Camera camera(
        LOOK_FROM, 
        LOOK_AT, 
        V_UP, V_FOV, 
        ASPECT_RATIO
    );

    // Engine
    int samplesPerPixel;
    cmdl("s", 10) >> samplesPerPixel;
    const RayTracing::Engine engine(image, scene, camera, samplesPerPixel);

    // Render
    if (cmdl("p")) {
        std::size_t hardwareConcurrency;
        cmdl("p") >> hardwareConcurrency;
        hardwareConcurrency = hardwareConcurrency == 0 ? 
            std::thread::hardware_concurrency() / 2 : hardwareConcurrency;
        engine.render(RayTracing::ParallelRenderer(hardwareConcurrency));
    } else {
        engine.render();
    }

    return EXIT_SUCCESS;

}
