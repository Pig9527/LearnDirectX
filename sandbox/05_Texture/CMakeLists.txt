cmake_minimum_required(VERSION 3.15)

project(05_TextureCube)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(05_Texture WIN32 TextureMain.cpp )

target_include_directories(05_Texture PRIVATE ${INCLUDE_DIR})
target_link_directories(05_Texture PRIVATE ${LIB_DIR})
set_target_properties(05_Texture PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 05_Texture
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
