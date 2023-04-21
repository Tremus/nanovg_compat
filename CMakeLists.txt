cmake_minimum_required(VERSION 3.15)
project(nanovg_compat VERSION 1.0.0 LANGUAGES C)

set(NANOVG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg_compat.c)
if(APPLE)
    list(APPEND NANOVG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg_compat.m)
endif()

add_library(${PROJECT_NAME} STATIC ${NANOVG_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/nanovg_dx11/src
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/MetalNanoVG/src
)

if(APPLE)
    set_property (TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY
                    COMPILE_FLAGS "-fobjc-arc")
endif()
