cmake_minimum_required(VERSION 3.15)

project(SFMLProj.out)
set(CMAKE_BUILD_TYPE Release)
message(${CMAKE_SYSTEM_NAME})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

    add_executable(test.out src/test.cpp) 
    add_compile_options(-fsanitize=address) 
    add_link_options(-fsanitize=address)

    add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/Gamew.cpp
        src/gui/Button.cpp
        src/gui/Label.cpp
        src/gui/DebugInfo.cpp
        src/Background.cpp
        src/gui/TextBox.cpp
        src/TileMap.cpp
        src/Player.cpp
        src/Animation.cpp
        src/Debug.cpp
        src/HandleEvent.cpp
        src/Enemy.cpp
        src/Gun.cpp
        src/Bullet.cpp
        src/AnimHuman.cpp
        src/SplashOfBlood.cpp
        src/gui/Interface.cpp
        src/Obj.cpp
    ) 
    find_package(SFML REQUIRED COMPONENTS 
        system
        window 
        graphics
    )
    target_link_libraries(${PROJECT_NAME} 
        pthread 
        sfml-system
        sfml-window
        sfml-graphics
    )
    target_link_libraries(test.out
        pthread
        sfml-system
        sfml-window
        sfml-graphics
    )
    set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20 
    CXX_STANDARD_REQUIRED ON) 
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

endif()
