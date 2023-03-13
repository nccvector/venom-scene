cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)

project(venom-scene)

add_subdirectory(ext)

set(VenomScene_DEBUG_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/raylib
)

# Set VenomScene include directories
set(VenomScene_INCLUDE_DIRS
  ${EIGEN_INCLUDE_DIR}
#  ${VenomCore_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/DebugViewer
)

# Propagate to parent
set(VenomScene_INCLUDE_DIRS ${VenomScene_INCLUDE_DIRS} PARENT_SCOPE)

message("================================================================================")
message("PROJECT NAME: ${PROJECT_NAME}")
message("INCLUDE DIRs: ${VenomScene_INCLUDE_DIRS}")
message("================================================================================")


include_directories(
  ${VenomScene_INCLUDE_DIRS}
  ${VenomScene_DEBUG_INCLUDE_DIRS}
)

set(VenomScene_SOURCES
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${VenomScene_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
