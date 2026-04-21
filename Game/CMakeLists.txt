# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.5)

# set the project name
project(GameAIPractical)

set(SFML_USE_STATIC_STD_LIBS OFF CACHE BOOL "" FORCE )
add_subdirectory("ext/SFML-2.5.1")
include_directories("ext/SFML-2.5.1/include")
include_directories("ext/h_files")

#add_library(myLibrary INTERFACE)
#target_include_directories(myLibrary INTERFACE {ext/h_files/})

include_directories("./") 

# add the executable "hello_world", which only uses single file "main.cpp"
#add_executable(hello_world main_hello_world.cpp)
add_executable(game main_game.cpp)
#add_executable(sfml_test main_sfml_test.cpp)

#target_link_libraries(sfml_test sfml-system sfml-graphics sfml-audio)
#target_link_libraries(sfml_test sfml-system sfml-graphics sfml-audio)

#add_executable(sfml_test main_sfml_test.cpp)
#target_link_libraries(sfml_test sfml-system sfml-graphics sfml-audio)
target_link_libraries(game sfml-system sfml-graphics sfml-audio)

#add_library(myLibrary INTERFACE)
#target_include_directories(myLibrary INTERFACE {ext/h_files/})

