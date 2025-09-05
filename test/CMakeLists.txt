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
    )

set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/SfDrawer.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )
