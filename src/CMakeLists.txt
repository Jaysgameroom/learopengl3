link_directories("${CMAKE_SOURCE_DIR}/libs")
include_directories("${CMAKE_SOURCE_DIR}/include" "src")

if(APPLE)
link_libraries("-lglfw3" "-framework Cocoa" "-framework IOKit" "-framework OpenGL")
else()
link_libraries("-lglfw3" "-lGL")
endif()


set(GLAD "${CMAKE_SOURCE_DIR}/deps/glad/glad.c")

add_executable(hello_window helloWindow.cpp ${GLAD})
add_executable(hello_triangle helloTriangle.cpp ${GLAD})
add_executable(hello_shader helloShader.cpp ${GLAD})


add_custom_target(copy_shaders ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/
	${CMAKE_CURRENT_BINARY_DIR}/shaders/
	COMMENT "IS THIS WORKING"
)




