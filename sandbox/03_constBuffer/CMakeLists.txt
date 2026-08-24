cmake_minimum_required(VERSION 3.15)

project(03_UseConstBuffer)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(03_UseConstBufferDrawRect WIN32 ConstBufferMain.cpp )

target_include_directories(03_UseConstBufferDrawRect PRIVATE ${INCLUDE_DIR})
target_link_directories(03_UseConstBufferDrawRect PRIVATE ${LIB_DIR})
set_target_properties(03_UseConstBufferDrawRect PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 03_UseConstBufferDrawRect
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
)
