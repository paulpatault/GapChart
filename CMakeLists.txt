cmake_minimum_required(VERSION 3.15)
project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(/usr/local/include)

include_directories(/usr/patault/Documents/GitHub/ProjetInfoGraphique\ jet1/includes)


include_directories(/usr/local/Cellar/opencv@2/2.4.13.7_6/include)
set(OPENCV_LIBS /usr/local/Cellar/opencv@2/2.4.13.7_6/lib/libopencv_core.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_6/lib/libopencv_imgproc.dylib
        /usr/local/Cellar/opencv@2/2.4.13.7_6/lib/libopencv_highgui.dylib)

set(OpenCV_VERSION 2.4.13.7)
set(PACKAGE_VERSION ${OpenCV_VERSION})

set(PACKAGE_VERSION_EXACT False)
set(PACKAGE_VERSION_COMPATIBLE False)

if(PACKAGE_FIND_VERSION VERSION_EQUAL PACKAGE_VERSION)
    set(PACKAGE_VERSION_EXACT True)
    set(PACKAGE_VERSION_COMPATIBLE True)
endif()

if(PACKAGE_FIND_VERSION VERSION_LESS PACKAGE_VERSION)
    set(PACKAGE_VERSION_COMPATIBLE True)
endif()


add_executable(main
        src/main.cpp
        src/data/LoadData.cpp
        src/data/LoadData.h
        includes/imgui/imgui.cpp
        includes/imgui/imgui.h
        src/data/Cylinder.cpp
        src/data/Cylinder.h
        src/screen/MVP.cpp
        src/screen/MVP.h
        includes/constants.h
        src/screen/c_ImGui.cpp
        src/screen/c_ImGui.h
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
        src/screen/Render.cpp
        src/screen/Render.h
        src/data/VAO.cpp
        src/data/VAO.h
        src/data/VBO.cpp
        src/data/VBO.h
        src/screen/Display.cpp
        src/screen/Display.h
        includes/variables.h
        src/data/Shader.cpp
        src/data/Shader.h
        includes/utils.h
        src/data/Texture.cpp
        src/data/Texture.h
        src/screen/Camera.cpp
        src/screen/Camera.h
        src/screen/Lamp.cpp
        src/screen/Lamp.h)


set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glfw3 3.3 REQUIRED)


target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(main glfw GLEW::GLEW ${OPENGL_gl_LIBRARY} ${OPENCV_LIBS})