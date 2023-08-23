cmake_minimum_required(VERSION 3.15)

project(SFMLProj)


message(${CMAKE_SYSTEM_NAME})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

add_executable(test.out src/test.cpp)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address -lX11)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Gamew.cpp
    src/Button.cpp
    src/Obj.cpp
    src/Label.cpp
    src/DebugInfo.cpp
    src/Background.cpp
    src/TextBox.cpp
    src/TileMap.cpp
)
find_package(SFML REQUIRED COMPONENTS system window graphics)
target_link_libraries(${PROJECT_NAME}
    pthread
    sfml-system 
    sfml-window 
    sfml-graphics
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")


endif()
