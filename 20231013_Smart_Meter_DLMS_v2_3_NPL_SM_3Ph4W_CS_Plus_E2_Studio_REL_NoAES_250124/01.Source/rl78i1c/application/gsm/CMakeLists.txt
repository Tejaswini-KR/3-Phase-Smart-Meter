cmake_minimum_required(VERSION 3.5.0)

project(gsm_fsm VERSION 0.1.0 LANGUAGES C)

#include(CTest)
#enable_testing()

file(GLOB PROJECT_SRC_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c" "src/test/*.c")

add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})

SET(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -DSIMULATION")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DSIMULATION")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
