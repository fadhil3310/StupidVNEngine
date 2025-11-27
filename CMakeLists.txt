cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(main 
    src/main.cpp
    src/utils.hpp
    src/umum.cpp
    src/scenes/scene.hpp
    src/pages/page.hpp
    src/engine/canvas.hpp
    src/engine/canvas.cpp
    src/engine/ui.hpp
    src/engine/ui.cpp
    src/engine/page_manager.hpp
    src/engine/page_manager.cpp
    src/engine/engine.hpp
    src/engine/engine.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

add_custom_target(
    customTarget
    COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:main>
)
add_dependencies(main customTarget)

add_custom_command(TARGET customTarget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:main>
)