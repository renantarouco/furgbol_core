cmake_minimum_required(VERSION 3.12)
project(FurgbolCore)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories("include")

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist")

## MODELS ##
set(MODELS_PATH "include/models")
set(MODELS
    "point"
    "line"
    "arc"
    "field"
    "camera_calibration"
    "ball"
    "robot")
foreach(MODEL ${MODELS})
    list(APPEND MODELS_H "${MODELS_PATH}/${MODEL}.h")
endforeach()
install(FILES ${MODELS_H} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/models")

## COMMUNICATION ##
add_library(communication SHARED
    "src/communication/multicast_receiver.cpp")
target_include_directories(communication PUBLIC
    ${Boost_INCLUDE_DIRS})
target_link_libraries(communication
    ${Boost_LIBRARIES})
set_target_properties(communication PROPERTIES
    PUBLIC_HEADER
        "include/communication/multicast_receiver.h")

## DATA_MANAGEMENT ##
add_library(data_management SHARED
    "src/data_management/sensor_loader.cpp")
target_link_libraries(data_management
    ${CMAKE_DL_LIBS})
set_target_properties(data_management PROPERTIES
    PUBLIC_HEADER
        "include/data_management/sensor_loader.h")

## SERIALIZATION ##
file(GLOB SSL_PROTO_FILES "src/serialization/ssl_proto/*.proto")
protobuf_generate_cpp(SSL_PROTO_CPP SSL_PROTO_H ${SSL_PROTO_FILES})
add_library(ssl_proto SHARED
    ${SSL_PROTO_CPP})
target_include_directories(ssl_proto PUBLIC
    ${Protobuf_INCLUDE_DIRS})
target_link_libraries(ssl_proto
    ${Protobuf_LIBRARIES})
set_target_properties(ssl_proto PROPERTIES
    PUBLIC_HEADER
        "${SSL_PROTO_H}")

## VIRTUAL_SENSORS ##
install(FILES
    "include/virtual_sensors/isensor.h"
    "include/virtual_sensors/sensor_assembly/internals.h"
    "include/virtual_sensors/sensor_assembly/sensor_assembly.h"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/virtual_sensors")

install(TARGETS
        communication
        ssl_proto
        data_management
    EXPORT FurgbolCoreTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include")

export(EXPORT FurgbolCoreTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/furgbol_core/FurgbolCoreTargets.cmake"
    NAMESPACE FurgbolCore::)
configure_file("cmake/FurgbolCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/furgbol_core/FurgbolCoreConfig.cmake"
    COPYONLY)
install(EXPORT FurgbolCoreTargets
    FILE FurgbolCoreTargets.cmake
    NAMESPACE FurgbolCore::
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake")
configure_file("cmake/FurgbolCoreConfig.cmake"
    "${CMAKE_INSTALL_PREFIX}/lib/cmake/FurgbolCoreConfig.cmake")


