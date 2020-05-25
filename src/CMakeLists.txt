PROJECT(macbookpro14-3)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)

SET(PROJECT_DESCRIPTION "https://github.com/sonals/macbookpro14-3")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost
  REQUIRED COMPONENTS iostreams)

set (SRC "nvram.cpp")

add_executable(qmap ${SRC})

target_link_libraries(qmap
  pthread
  ${Boost_IOSTREAMS_LIBRARY}
  )
