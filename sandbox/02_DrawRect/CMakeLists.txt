cmake_minimum_required(VERSION 3.15)

project(02_DrawARect)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(02_DrawARect WIN32 DrawRectMain.cpp )

target_include_directories(02_DrawARect PRIVATE ${INCLUDE_DIR})
target_link_directories(02_DrawARect PRIVATE ${LIB_DIR})
set_target_properties(02_DrawARect PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 02_DrawARect
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
)
