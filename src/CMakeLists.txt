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
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    )

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )