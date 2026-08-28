cmake_minimum_required(VERSION 3.15)
project(LearDirecX11WithWindowSDK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-DUNICODE" "-D_UNICODE")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
# target_include_directories(cube PRIVATE
#     src/core 
#     src/core/Event
#     src/render 
#     src/window 
#     src/Gemotry 
#     src/Graphic 
#     src/Graphic/shader  
#     src
#     vendor/imgui vendor
# )

set(INCLUDE_DIR  core
  ${CMAKE_SOURCE_DIR}/engine
  ${CMAKE_SOURCE_DIR}/engine/core/event
  ${CMAKE_SOURCE_DIR}/engine/Gemotry
  ${CMAKE_SOURCE_DIR}/engine/Graphic
  ${CMAKE_SOURCE_DIR}/engine/render
  ${CMAKE_SOURCE_DIR}/engine/window
  ${CMAKE_SOURCE_DIR}/vendor/stb_image/
  ${CMAKE_SOURCE_DIR}/vendor/
  ${CMAKE_SOURCE_DIR}/vendor/imgui/)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/lib)

add_subdirectory(engine)

add_subdirectory(sandbox/01_DrawTriangle)
add_subdirectory(sandbox/02_DrawRect)
add_subdirectory(sandbox/03_constBuffer)
add_subdirectory(sandbox/04_light)
add_subdirectory(sandbox/05_Texture)
add_subdirectory(sandbox/06_Camera)

target_link_libraries(01_DrawATriangle engine)
target_link_libraries(02_DrawARect engine)
target_link_libraries(04_Light engine)
target_link_libraries(05_Texture engine)
target_link_libraries(06_Camera engine)
# file(GLOB_RECURSE SOURCES 
#   "src/core/*.cpp" 
#   "src/Graphic/*.cpp"
#   "src/Graphic/shader/*.cpp"  
#   "src/render/*.cpp" 
#   "src/window/*.cpp" 
#   "src/core/Event/*.cpp"
#   src/Gemotry/Model.cpp
# )
# file(GLOB_RECURSE HEADERS 
#   "src/core/*.h"
#   "src/Graphic/*.h" 
#   "src/Graphic/shader/*.h" 
#   "src/render/*.h"
#   "src/window/*.h" 
#   "src/core/Event/*.h"
#   src/Gemotry/Model.h
# )

# add_executable(cube src/main.cpp ${SOURCES} ${HEADERS} src/pheader.h )



# target_link_directories(cube PRIVATE vendor/lib)
# # 链接 DirectX 库
# target_link_libraries(cube
#     d3d11
#     d3dcompiler
#     dxgi
#     imgui_dx11
#     assimp-vc142-mtd

# )

# set_target_properties(cube PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
# target_compile_definitions(cube PRIVATE -DUNICODE -D_UNICODE)
