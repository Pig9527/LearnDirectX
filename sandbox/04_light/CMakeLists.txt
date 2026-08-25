cmake_minimum_required(VERSION 3.15)

project(04_DrawShapeWithLight)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(04_Light WIN32 lightMain.cpp )

if (MSVC)
    # 为 C 和 CXX (C++) 语言添加 /utf-8 编译选项
    add_compile_options("$<$<COMPILE_LANGUAGE:C>:/utf-8>")
    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/utf-8>")
endif()

target_include_directories(04_Light PRIVATE ${INCLUDE_DIR})
target_link_directories(04_Light PRIVATE ${LIB_DIR})
set_target_properties(04_Light PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries( 04_Light
  d3d11
  d3dcompiler
  dxgi
  engine
  imgui_dx11
  assimp-vc142-mtd
)
