
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFML_DIR "d:/devtools/mingw-w64/Libs/SFML-2.5.1/lib/cmake/SFML")

set(GLEW_VERBOSE "1")




find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)



add_executable(untitled main.cpp)
target_link_libraries(untitled sfml-graphics GLEW ${OPENGL_gl_LIBRARY})
