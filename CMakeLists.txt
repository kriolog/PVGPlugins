cmake_minimum_required(VERSION 2.8)
project(ParaViewGeo_plugins)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(BUILD_SHARED_LIBS ON)

find_package(ParaView REQUIRED)
include("${PARAVIEW_USE_FILE}")
include(ParaViewPlugins)
# set(ParaView_CMAKE_DIR "${ParaView_SOURCE_DIR}/CMake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ParaView_CMAKE_DIR})

find_package(VTK REQUIRED)
include_directories(${VTK_INCLUDE_DIRS})
# set(VTK_CMAKE_DIR "${ParaView_SOURCE_DIR}/VTK/CMake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VTK_CMAKE_DIR})
include(vtkExternalModuleMacros)

add_subdirectory(Filters/ConvertPointsToBlocks)
add_subdirectory(Filters/PolyToStruct)
add_subdirectory(NonBSDPlugins/tetgen)
