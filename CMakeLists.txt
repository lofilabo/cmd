cmake_minimum_required(VERSION 2.8)
project(cmd)

ENABLE_TESTING()
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

SET(HDRS 
  cmd.h
)

SET(SRCS
  cmd.c
)

add_executable(cmd ${SRCS} ${HDRS})
target_link_libraries(cmd m ncurses readline)

install(
  TARGETS cmd
  RUNTIME DESTINATION bin
)
