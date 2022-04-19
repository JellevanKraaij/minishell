cmake_minimum_required(VERSION 3.16.3)

project(minishell)

set (MAIN_SRCS src/main.c)
set (UTIL_SRCS
	src/error.c
)
set (EXEC_NAME minishell)

#compiler settings:
set (CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set (CMAKE_C_FLAGS_DEBUG "-g -fsanitize=address") #cmake -DCMAKE_BUILD_TYPE=DEBUG to add debug flags
set (CMAKE_EXPORT_COMPILE_COMMANDS ON) #vscode include path checking

#make executable with output name specified under EXEC_NAME and sources specified under UTIL_SRCS and MAIN_SRCS
add_executable(${EXEC_NAME} ${MAIN_SRCS} ${UTIL_SRCS})
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#add libft:
add_subdirectory(lib/libft)
#link libs
target_link_libraries(${EXEC_NAME} readline ft)

#----------- TESTING -----------#
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	minishell_tests
	test/minishell_tests.cpp
	${UTIL_SRCS}
)
target_include_directories(minishell_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(
	minishell_tests
	gtest_main
	gmock_main
)

include(GoogleTest)
gtest_discover_tests(minishell_tests)