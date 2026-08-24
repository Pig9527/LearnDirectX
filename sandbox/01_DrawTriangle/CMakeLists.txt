cmake_minimum_required(VERSION 3.15)

project(01_DrawATriangle)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(01_DrawATriangle WIN32 DrawTriangleMain.cpp )

target_include_directories(01_DrawATriangle PRIVATE ${INCLUDE_DIR})
target_link_directories(01_DrawATriangle PRIVATE ${LIB_DIR})
set_target_properties(01_DrawATriangle PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 01_DrawATriangle
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
)
