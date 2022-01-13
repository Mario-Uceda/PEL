cmake_minimum_required(VERSION 3.12)

project(dlib1
   VERSION 0.1.0
   DESCRIPTION "Proyecto sencillo de C++ con un solo target"
   LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

get_target_property(CFEATURES ${PROJECT_NAME} COMPILE_FEATURES)
message("-- Target compile features: ${CFEATURES}")

set_target_properties(${PROJECT_NAME} PROPERTIES
   CXX_EXTENSIONS OFF
   RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
   RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
)

#-------------------------------------------------------------------
# política de avisos:

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
   target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
   target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

get_target_property(CFLAGS ${PROJECT_NAME} COMPILE_OPTIONS)
message("-- Target compile options: ${CFLAGS}")

#-------------------------------------------------------------------
# integración de bibliotecas de terceros:

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(range-v3 REQUIRED)
find_package(dlib REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
   fmt::fmt
   nlohmann_json
   range-v3
   dlib::dlib
)