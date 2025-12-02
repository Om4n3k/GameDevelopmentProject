cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Engine)

set(PROJECT_SOURCE_FILES
	source/Engine.h
	source/Engine.cpp
	source/Application.h
	source/Application.cpp
	source/eng.h
	source/input/InputManager.cpp
	source/input/InputManager.h
	source/graphics/ShaderProgram.cpp
	source/graphics/ShaderProgram.h
		source/graphics/GraphicsApi.cpp
		source/graphics/GraphicsApi.h
		source/render/Material.cpp
		source/render/Material.h
		source/render/Mesh.cpp
		source/render/Mesh.h
		source/graphics/VertexLayout.h
		source/render/RenderQueue.cpp
		source/render/RenderQueue.h
		source/scene/GameObject.cpp
		source/scene/GameObject.h
		source/scene/Scene.cpp
		source/scene/Scene.h
)

include_directories(source)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
include_directories(thirdparty/glfw-3.4/include)

# Add Glew library
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
include_directories(${CMAKE_SOURCE_DIR}/engine/thirdparty/glew/include)
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew PROPERTY FOLDER GLEW)

# Link all thirdparty libraries
target_link_libraries(${PROJECT_NAME} 
    glfw 
    glew_s
)
