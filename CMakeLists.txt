cmake_minimum_required(VERSION 3.5.0)
project(SDLCards VERSION 0.1.0 LANGUAGES C CXX)

add_executable(SDLCards
                app.cpp
                card.cpp
                exception.cpp
                main.cpp
                paciencia.cpp
                render.cpp
                thread.cpp
                imgui/imgui_demo.cpp
                imgui/imgui_draw.cpp
                imgui/imgui_tables.cpp
                imgui/imgui_widgets.cpp
                imgui/imgui.cpp
                imgui/backends/imgui_impl_sdl2.cpp
                imgui/backends/imgui_impl_sdlrenderer2.cpp 
               ) 
target_link_libraries(SDLCards SDL2 SDL2_image SDL2_ttf curl)
target_include_directories(SDLCards PRIVATE imgui imgui/backends /usr/include/SDL2)