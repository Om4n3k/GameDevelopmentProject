cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project (GameDevelopmentProject)

set(PROJECT_SOURCE_FILES
  source/main.cpp
  source/Game.cpp
  source/Game.h
)
# Add the application
include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add engine library
add_compile_definitions(GLEW_NO_GLU)
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")
include_directories(engine/source)
include_directories(engine/thirdparty/glew/include)
target_link_libraries(${PROJECT_NAME}
    Engine
)