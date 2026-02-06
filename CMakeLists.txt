cmake_minimum_required(VERSION 3.23)
project(opengl)

link_directories("libs")
include_directories("include" "src")

if(APPLE)
link_libraries("-lglfw3" "-framework Cocoa" "-framework IOKit" "-framework OpenGL")
else()
link_libraries("-lglfw3" "-lGL")
endif()



set(GLAD "deps/glad/glad.c")

add_executable(hello_window src/helloWindow.cpp ${GLAD})
add_executable(hello_triangle src/helloTriangle.cpp ${GLAD})





