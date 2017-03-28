cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(WCG4)

option(WITH_GEANT$_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include (${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(WCG4 WCG4.cc ${sources} ${headers})
target_link_libraries(WCG4 ${Geant4_LIBRARIES})

set(WCG4_SCRIPTS 
  WCG4.in
  )

foreach(_script ${EXAMPLES_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
