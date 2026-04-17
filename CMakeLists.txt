cmake_minimum_required(VERSION 3.11)
project(Loro C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(Loro
    src/main.c

    src/core/apps.c

    src/ui/theme.c
    src/ui/window.c
    src/ui/search_bar.c
    src/ui/apps.c
)

target_include_directories(Loro PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Loro raylib)
