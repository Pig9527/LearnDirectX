cmake_minimum_required(VERSION 3.15)

project(05_TextureCube)

set(CMAKE_CXX_STANDARD 17)

# message(status ${SOURCES})

add_executable(05_Texture WIN32 TextureMain.cpp )

if (MSVC)
    # 为 C 和 CXX (C++) 语言添加 /utf-8 编译选项
    add_compile_options("$<$<COMPILE_LANGUAGE:C>:/utf-8>")
    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/utf-8>")
endif()

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