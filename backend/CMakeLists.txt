cmake_minimum_required(VERSION 3.16)
project(robot_status_interface CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release by default for Pi deploys; override with -DCMAKE_BUILD_TYPE=Debug locally
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Crow uses standalone Asio (not Boost::Asio) per its own docs.
# On macOS: brew install asio
# On the Pi (Ubuntu): sudo apt install libasio-dev
find_package(Threads REQUIRED)
find_path(ASIO_INCLUDE_DIR asio.hpp)

if(NOT ASIO_INCLUDE_DIR)
  message(FATAL_ERROR "Asio headers not found. macOS: brew install asio | Ubuntu: sudo apt install libasio-dev")
endif()

include(FetchContent)
FetchContent_Declare(
  Crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.2.1.2
)
FetchContent_MakeAvailable(Crow)

add_executable(robot_status_server
  src/main.cpp
  src/vitals.cpp
)

target_include_directories(robot_status_server PRIVATE include ${ASIO_INCLUDE_DIR})

# Tell Crow to use standalone Asio instead of Boost::Asio
target_compile_definitions(robot_status_server PRIVATE CROW_USE_ASIO ASIO_STANDALONE)

target_link_libraries(robot_status_server
  PRIVATE
    Crow::Crow
    Threads::Threads
)