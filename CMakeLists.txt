cmake_minimum_required(VERSION 3.20)
project(wavy)

set (CMAKE_CXX_STANDARD 17)

if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

add_executable(main main.cc)
target_link_libraries(main ${CMAKE_SOURCE_DIR}/libraylib.a)
