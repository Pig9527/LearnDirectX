cmake_minimum_required(VERSION 3.15)

project(06_CameraCube)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(06_Camera WIN32 CameraMain.cpp )

target_include_directories(06_Camera PRIVATE ${INCLUDE_DIR})
target_link_directories(06_Camera PRIVATE ${LIB_DIR})
set_target_properties(06_Camera PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 06_Camera
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
