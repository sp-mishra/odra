cmake_minimum_required(VERSION 3.5)

project(odra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_FLAGS_DISTRIBUTION "-E")
set(CMAKE_C_FLAGS_DISTRIBUTION "-E")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

#add_compile_definitions(FMT_CONSTEVAL= )
add_definitions(-DFMT_CONSTEVAL= )
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
add_compile_definitions(BOOST_ALL_NO_LIB)
add_compile_definitions(Boost_USE_STATIC_LIBS)
set(Boost_USE_STATIC_LIBS ON)

set(PROJECT_NAME odra)
include(CMakePrintHelpers)
include_directories(/usr/local/include)
include_directories(src/main/)
include_directories(src/third_party/)
include_directories(src/third_party/fmt/include)

if(NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
include_directories(src/third_party/spdlog/include)
add_subdirectory(src/third_party/spdlog)
find_package(spdlog QUIET)
endif()

file(GLOB_RECURSE
    BOOST_SOURCE_FILES
    src/third_party/boost/*.h
    src/third_party/boost/*.hpp
)

file(GLOB
    MAIN_SRC
    main.cpp
    src/main/*.cpp
    src/main/*.hpp
)

add_executable(${PROJECT_NAME}
    ${MAIN_SRC}
    ${BOOST_SOURCE_FILES}
)

if(NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        spdlog::spdlog
    )
else()
#    target_link_libraries(
#        ${PROJECT_NAME}
#        PRIVATE
#        spdlog::spdlog_header_only
#    )
endif()

message("CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})
install(TARGETS odra
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
