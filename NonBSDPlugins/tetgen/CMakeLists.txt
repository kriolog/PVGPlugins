project(Tetgen)

if(ParaView_SOURCE_DIR)
  include_directories(${VTK_INCLUDE_DIRS})
else()
  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
endif()

# include generated ui_*.h files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(Module_SRCS
  pq${PROJECT_NAME}.h
  pq${PROJECT_NAME}.cxx
)

set(Module_MOC_HDRS
  pq${PROJECT_NAME}.h
)

set(Module_UI_FILES
  pq${PROJECT_NAME}.ui
)

pv_qt_wrap_cpp(__Module_MOC_SRCS ${Module_MOC_HDRS})
pv_qt_wrap_ui(__Module_UI_SRCS ${Module_UI_FILES})

set (outifaces)
set (outsrcs)
add_paraview_property_group_widget(
  outifaces
  outsrcs
  TYPE "${PROJECT_NAME}Widget"
  CLASS_NAME pq${PROJECT_NAME}
)

add_paraview_plugin(
  ${PROJECT_NAME}SMPlugin "1.0"
  SERVER_MANAGER_XML ${PROJECT_NAME}.xml
  SERVER_MANAGER_SOURCES vtk${PROJECT_NAME}.cxx
  GUI_INTERFACES ${outifaces}
  SOURCES
    ${outsrcs}
    ${Module_SRCS}
    ${__Module_RESOURCE_SRCS}
    ${__Module_MOC_SRCS}
    ${__Module_UI_SRCS}
    tetgen.cxx
    predicates.cxx
)
