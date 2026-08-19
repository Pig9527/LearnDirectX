cmake_minimum_required(VERSION 3.15)
project(cube)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES 
  "src/core/*.cpp" 
  "src/Graphic/*.cpp"
  "src/Graphic/shader/*.cpp"  
  "src/render/*.cpp" 
  "src/window/*.cpp" 
  "src/core/Event/*.cpp"
  src/Gemotry/Model.cpp
)
file(GLOB_RECURSE HEADERS 
  "src/core/*.h"
  "src/Graphic/*.h" 
  "src/Graphic/shader/*.h" 
  "src/render/*.h"
  "src/window/*.h" 
  "src/core/Event/*.h"
  src/Gemotry/Model.h
)

add_executable(cube src/main.cpp ${SOURCES} ${HEADERS} src/pheader.h )

target_include_directories(cube PRIVATE
    src/core 
    src/core/Event
    src/render 
    src/window 
    src/Gemotry 
    src/Graphic 
    src/Graphic/shader  
    src
    vendor/imgui vendor
)

target_link_directories(cube PRIVATE vendor/lib)
# 链接 DirectX 库
target_link_libraries(cube
    d3d11
    d3dcompiler
    dxgi
    imgui_dx11
    assimp-vc142-mtd

)

set_target_properties(cube PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
target_compile_definitions(cube PRIVATE -DUNICODE -D_UNICODE)
