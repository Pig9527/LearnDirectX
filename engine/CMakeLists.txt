cmake_minimum_required(VERSION 3.15)
project(engine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES 
  core/*.cpp 
  Geometry/*.cpp
  Entity/*.cpp
  Graphic/*.cpp
  render/*.cpp
  window/*.cpp
  )
file(GLOB_RECURSE HEADERS 
  core/*.h
  Geometry/*.h
  Entity/*.h
  Graphic/*.h
  render/*.h 
  window/*.h
  )

add_library(engine ${SOURCES} ${HEADERS})

target_include_directories(
  engine PRIVATE
  ${INCLUDE_DIR}
)
message(status ${CMAKE_SOURCE_DIR})
target_link_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/vendor/lib)

target_link_libraries(engine
  dxgi d3d11 d3dcompiler imgui_dx11 assimp-vc142-mtd d2d1 dwrite
)
