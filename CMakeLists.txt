cmake_minimum_required(VERSION 3.30)
project(Proxy)

set(CMAKE_CXX_STANDARD 20)

find_package(cppzmq CONFIG REQUIRED)

include_directories(src/includes)

add_executable(Proxy src/main.cpp
        src/include/ProxyManager.h
        src/include/Proxy.h
        src/include/CustomAssert.h)
target_link_libraries(Proxy PRIVATE cppzmq cppzmq-static)