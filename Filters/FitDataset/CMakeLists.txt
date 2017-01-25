project(FitDataset)
find_package(ParaView REQUIRED)
include(${PARAVIEW_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/common)

add_paraview_plugin(
  ${PROJECT_NAME}SMPlugin "1.0"
  SERVER_MANAGER_XML ${PROJECT_NAME}.xml
  SERVER_MANAGER_SOURCES vtk${PROJECT_NAME}.cpp
  SERVER_SOURCES
    vtkConvexHull.cpp
    vtkLeastSquareFit.cpp
    Inc3dCHull_ConvexHull.cpp
    Inc3dCHull_Face.cpp
    Inc3dCHull_Edge.cpp
    Inc3dCHull_Vertex.cpp
    ${CMAKE_SOURCE_DIR}/common/vtkCoordinateSystemMapper.cpp
)
