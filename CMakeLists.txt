cmake_minimum_required(VERSION 3.9.0)
cmake_policy(SET CMP0077 NEW)

project(lcdscrub)

add_subdirectory(bezbios)

add_executable(lcdscrub main.cpp)
target_link_libraries(lcdscrub crt sched tlay2_uart interrupts ega crt)
package_floppy(lcdscrub)