cmake_minimum_required(VERSION 3.10)
project(ftdi_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(LibFTDI_LIBRARY libftdi1)

link_directories(/usr/lib/arm-linux-gnueabihf)

add_executable(${PROJECT_NAME} ftdi_app.cpp)

#target_link_libraries(${PROJECT_NAME} ${LibFTDI_LIBRARY})
target_link_libraries(${PROJECT_NAME} /usr/lib/arm-linux-gnueabihf/libftdi.so) # Hardcoded for now
