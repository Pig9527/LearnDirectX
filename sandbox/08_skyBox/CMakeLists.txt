cmake_minimum_required(VERSION 3.15)

project(08_skyboxProj)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(08_skyBox WIN32 skyBoxMain.cpp )

target_include_directories(08_skyBox PRIVATE ${INCLUDE_DIR})
target_link_directories(08_skyBox PRIVATE ${LIB_DIR})
set_target_properties(08_skyBox PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 08_skyBox
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
