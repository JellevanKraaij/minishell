cmake_minimum_required(VERSION 3.23.0)

project(hello-world)
set (SRCS src/main.c)
set (EXEC_NAME hello-world)

#compiler settings:
set (CMAKE_C_COMPILER gcc)
set (CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set (CMAKE_C_FLAGS_DEBUG "-g -fsanitize=address") #cmake -DCMAKE_BUILD_TYPE=DEBUG to add debug flags
set (CMAKE_EXPORT_COMPILE_COMMANDS ON) #vscode include path checking

#norm rules so flclean and re work
add_custom_target(fclean make clean)
add_custom_target(re make clean COMMAND make)

#make executable with output name specified under EXEC_NAME and sources specified under SRCS
add_executable(${EXEC_NAME} ${SRCS})

target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#optionaly add libft:
# add_subdirectory(lib/libft)
# target_link_libraries(${EXEC_NAME} PRIVATE ft)
