cmake_minimum_required(VERSION 3.0.0)
add_compile_options(-std=c++11)

project(libjson LANGUAGES CXX)

include_directories(include)

file(GLOB JSONCPP_SRCS
    "include/json*.h"
    "src/lib_json/*.h"
    "src/lib_json/*.cpp"
    "src/lib_json/*.inl"
    )

add_library(jsoncpp_static STATIC ${JSONCPP_SRCS})
