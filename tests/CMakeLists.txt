project(RayTracing)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/b5fd99bbd55ebe1a3488b8ea3717fba089293457.zip DOWNLOAD_EXTRACT_TIMESTAMP ON)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main.test main.test.cpp)
target_link_libraries(main.test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(main.test)