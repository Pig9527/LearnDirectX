cmake_minimum_required(VERSION 3.15)

project(imguiexample)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(imgui_dx11 STATIC)

set(IMGUI_SOURCES imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp 
    imgui/imgui_tables.cpp 
    imgui/imgui_widgets.cpp 
    imgui/backends/imgui_impl_win32.cpp 
    imgui/backends/imgui_impl_dx11.cpp 
)

set(IMGUI_HEADERS 
    imgui/imgui.h 
    imgui/imconfig.h 
    imgui/imgui_internal.h 
    imgui/backends/imgui_impl_dx11.h 
    imgui/backends/imgui_impl_win32.h 
)

target_sources(imgui_dx11 PRIVATE ${IMGUI_SOURCES})
target_include_directories(imgui_dx11 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui
   ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)

target_link_directories(imgui_dx11 PUBLIC 
  d3d11 
  dxgi 
  d3dcompiler
  PRIVATE winmm ${CMAKE_DL_LIBS})

source_group("Sources" FILES ${IMGUI_SOURCES})
source_group("Headers" FILES ${IMGUI_HEADERS})

message(STATUS "Building ImGui with DX11 and Win32 backend")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")


