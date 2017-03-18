SET(execName eqinterpreter)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(SPECIAL_OS_LIBS "pthread")
SET(EXECUTABLE_OUTPUT_PATH ".")

SET(SRC_FOLDER "Eq Interpreter")
FILE(GLOB_RECURSE SRC_FILES "${SRC_FOLDER}/*.cpp")

ADD_EXECUTABLE(${execName} ${SRC_FILES})
set_property(TARGET ${execName} PROPERTY OUTPUT_NAME "eqinterpreter")

include_directories(${execName} ${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Linux/arm)
target_link_libraries(${execName} ${CMAKE_CURRENT_SOURCE_DIR}/Linux/arm/libntcore.a)

set (CMAKE_CXX_FLAGS "--std=c++11 -lstdc++ -g -O3 ${CMAKE_CXX_FLAGS}")
