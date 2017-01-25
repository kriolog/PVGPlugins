project(RelativeTransform)
find_package(ParaView REQUIRED)
include(${PARAVIEW_USE_FILE})

add_paraview_plugin(
  ${PROJECT_NAME}SMPlugin "1.0"
  SERVER_MANAGER_XML ${PROJECT_NAME}.xml
  SERVER_MANAGER_SOURCES vtk${PROJECT_NAME}.cxx
)
