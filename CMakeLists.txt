cmake_minimum_required(VERSION 3.10)
project(ftdi_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(LibFTDI_LIBRARY libftdi1)

add_executable(${PROJECT_NAME} ftdi_app.cpp)

if (WIN32)
  set(FTDI_LIB_PATH "../CDM-v2.12.36.4-WHQL-Certified/amd64")

  # Find the FTDI library on Windows (typically ftd2xx.lib)
  find_library(LibFTDI_LIBRARY ftd2xx.lib PATHS ${FTDI_LIB_PATH})

  # Add the library directory
  link_directories(${FTDI_LIB_PATH})

  # Optional: Include directories if FTDI headers are required
  set(FTDI_INCLUDE_PATH "../CDM-v2.12.36.4-WHQL-Certified/")
  include_directories(${FTDI_INCLUDE_PATH})

  # Print a message to confirm Windows build configuration
  message(STATUS "Building for Windows")
elseif (UNIX)
  # Raspberry pi
  link_directories(/usr/lib/arm-linux-gnueabihf)
  target_link_libraries(${PROJECT_NAME} /usr/lib/arm-linux-gnueabihf/libftdi.so) # Hardcoded for now
  
  # Print a message to confirm Linux build configuration
  message(STATUS "Building for Linux")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()