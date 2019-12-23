cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(/usr/local/include)

add_executable(main
        src/main.cpp
        src/data/LoadData.cpp
        src/data/LoadData.h
        includes/debugbreak.h
        includes/imgui/imgui.cpp
        includes/imgui/imgui.h
        includes/imgui/imgui_demo.cpp
        includes/imgui/imgui_draw.cpp
        includes/imgui/imgui_widgets.cpp
        includes/imgui/imgui_internal.h
        includes/imgui/imconfig.h
        includes/imgui/imstb_rectpack.h
        includes/imgui/imstb_textedit.h
        includes/imgui/imstb_truetype.h
        includes/imgui/imgui_impl_glfw.cpp
        includes/imgui/imgui_impl_glfw.h
        includes/imgui/imgui_impl_opengl3.cpp
        includes/imgui/imgui_impl_opengl3.h
        src/data/Cylinder.cpp src/data/Cylinder.h src/screen/MVP.cpp src/screen/MVP.h includes/constants.h src/screen/c_ImGui.cpp src/screen/c_ImGui.h src/screen/Render.cpp src/screen/Render.h src/data/LoadData2/LoadData2.cpp src/data/LoadData2/LoadData2.h src/data/VAO.cpp src/data/VAO.h src/data/VBO.cpp src/data/VBO.h src/screen/Display.cpp src/screen/Display.h includes/variables.h src/data/Shaders.cpp src/data/Shaders.h src/data/Arc.cpp src/data/Arc.h includes/utils.h includes/main_includes.h)

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)

#set(OpenCV_DIR=./usr/local/Cellar/opencv@2/2.4.13.7_5/share/OpenCV)
#SET(OpenCV_INCLUDE_DIR "./usr/local/Cellar/opencv@2")
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})


target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(main glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OpenCV_LIBS})