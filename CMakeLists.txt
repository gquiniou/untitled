
project(untitled CXX)

cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (OpenGL_GL_PREFERENCE LEGACY)

add_executable(untitled main.cpp)

IF (WIN32)
    set(SFML_DIR "d:/devtools/mingw-w64/Libs/SFML-2.5.1/lib/cmake/SFML")
    set(CMAKE_PREFIX_PATH "D:/devtools/mingw-w64/Libs/glew-2.1.0/")
    set(CMAKE_LIBRARY_PATH "D:/devtools/mingw-w64/Libs/glew-2.1.0/lib")
    set(GLEW_SHARED_LIBRARY_RELEASE "D:/devtools/mingw-w64/Libs/glew-2.1.0/lib")
    set(GLEW_INCLUDE_DIR "D:/devtools/mingw-w64/Libs/glew-2.1.0/include")
ENDIF (WIN32)

set(GLEW_VERBOSE "1")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)
set(CMAKE_PREFIX_PATH "D:/devtools/mingw-w64/Libs/glew-2.1.0/")
set(CMAKE_LIBRARY_PATH "D:/devtools/mingw-w64/Libs/glew-2.1.0/lib")

find_package(GLEW REQUIRED)

target_include_directories(untitled PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(untitled sfml-graphics GLEW::GLEW ${OPENGL_gl_LIBRARY})
target_compile_options(untitled PRIVATE -Werror -Wall -Wextra)
