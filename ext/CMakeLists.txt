# Configure the core 3rd party dependencies and their Variables

# Set eigen include path
set(EIGEN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eigen")

# Propagate to parent
set(EIGEN_INCLUDE_DIR ${EIGEN_INCLUDE_DIR} PARENT_SCOPE)

add_subdirectory(raylib)
