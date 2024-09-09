cmake_minimum_required(VERSION 3.16)

project(tests C)

add_executable(funny-queue src/startup.c src/funny-queue.c)
add_executable(number-words-text src/startup.c src/number-words-text.c)

include_directories(src)

enable_testing()
add_test(NAME run-funny-queue COMMAND funny-queue)
add_test(NAME run-number-words-text COMMAND number-words-text)