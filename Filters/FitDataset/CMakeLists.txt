project(FitDataset)

if(ParaView_SOURCE_DIR)
  include_directories(${VTK_INCLUDE_DIRS})
else()
  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
endif()

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
    ../../common/vtkCoordinateSystemMapper.cpp
)
