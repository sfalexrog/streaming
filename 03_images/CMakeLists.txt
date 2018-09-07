cmake_minimum_required(VERSION 3.1)
project(dalai_gamma)

add_executable(scale_gamma
    scale.cpp
    vec3.cpp
    )

add_executable(hdr_open
    hdr_open.cpp
    vec3.cpp
    )
