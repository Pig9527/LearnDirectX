cmake_minimum_required(VERSION 3.15)

project(09_noramlTexture)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(09_noramlTexture WIN32 NormalTexMain.cpp )

target_include_directories(09_noramlTexture PRIVATE ${INCLUDE_DIR})
target_link_directories(09_noramlTexture PRIVATE ${LIB_DIR})
set_target_properties(09_noramlTexture PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 09_noramlTexture
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
