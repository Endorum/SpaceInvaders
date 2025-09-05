# Model
set(ModelSources
    )


# Ensure C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AlienController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AliensController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BunkersController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayerController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/SoundsController.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/SfDrawer.cpp
    )

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )