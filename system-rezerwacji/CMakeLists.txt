cmake_minimum_required(VERSION 3.10)
project(rezerwacje CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gdzie leza pliki naglowkowe (.h)
include_directories(include)

# wszystkie pliki .cpp z folderu src
file(GLOB ZRODLA src/*.cpp)

add_executable(rezerwacje ${ZRODLA})
