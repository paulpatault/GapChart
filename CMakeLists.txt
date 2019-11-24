cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(/usr/local/include)

add_executable(main
        main.cpp
        src/myFiles/LoadData.cpp
        src/myFiles/LoadData.h
        src/dirGL/debugbreak.h
        src/imgui/imgui.cpp
        src/imgui/imgui.h
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_internal.h
        src/imgui/imconfig.h
        src/imgui/imstb_rectpack.h
        src/imgui/imstb_textedit.h
        src/imgui/imstb_truetype.h
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_glfw.h
        src/imgui/imgui_impl_opengl3.cpp
        src/imgui/imgui_impl_opengl3.h
        src/dirGL/Shaders.h
        src/dirGL/Window.h)

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