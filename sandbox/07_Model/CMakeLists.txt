cmake_minimum_required(VERSION 3.15)

project(07_ModelHouse)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(07_model WIN32 ModelMain.cpp )

target_include_directories(07_model PRIVATE ${INCLUDE_DIR})
target_link_directories(07_model PRIVATE ${LIB_DIR})
set_target_properties(07_model PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 07_model
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
