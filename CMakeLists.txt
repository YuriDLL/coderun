cmake_minimum_required(VERSION 3.16)

project(funny-queue C)

add_executable(${CMAKE_PROJECT_NAME} src/startup.c src/funny-queue.c)

set_source_files_properties(src/funny-queue.c PROPERTIES COMPILE_FLAGS -Dmain=testmain)

enable_testing()
add_test(NAME run-funny-queue COMMAND funny-queue)