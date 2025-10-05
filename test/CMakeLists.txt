enable_testing()

set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/control/AlienController.cpp
    ${CMAKE_SOURCE_DIR}/src/control/AliensController.cpp
    ${CMAKE_SOURCE_DIR}/src/control/BunkersController.cpp
    ${CMAKE_SOURCE_DIR}/src/control/PlayerController.cpp
    ${CMAKE_SOURCE_DIR}/src/control/SoundsController.cpp
    )

set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/Alien.hpp
    ${CMAKE_SOURCE_DIR}/src/model/Laser.hpp
    ${CMAKE_SOURCE_DIR}/src/model/Player.hpp
    ${CMAKE_SOURCE_DIR}/src/model/Bunker.hpp
    ${CMAKE_SOURCE_DIR}/src/model/Positionable.hpp
    )

set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/SfDrawer.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/GameTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BunkersControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayerControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AlienControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/AlienTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/BunkerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/LaserTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/PlayerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameStateTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/PositionableTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )

target_link_libraries(Test
    PRIVATE
        gtest gtest_main gmock pthread
        SFML::Graphics SFML::Audio
)

include(GoogleTest)
gtest_discover_tests(Test)


