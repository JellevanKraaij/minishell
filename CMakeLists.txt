# ------------------------------------- SETTINGS ---------------------------------- #
cmake_minimum_required(VERSION 3.16.3)

project(minishell)

set (MAIN_SRCS src/main.c)
set (UTIL_SRCS
	src/error.c
	src/signals.c
	src/parser/parser.c
	src/parser/t_token.c
	src/parser/t_command.c
	src/parser/t_file.c
	src/parser/lexer_process.c
	src/parser/utils.c
	src/parser/expand_vars.c
	src/parser/split_tokens.c
	src/parser/parse_tokens.c
	src/environment/ft_getenv.c
	src/environment/ft_environ.c
	src/environment/ft_unsetenv.c
)
set (EXEC_NAME minishell)

# compiler settings:
set (CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set (CMAKE_C_FLAGS_DEBUG "-g -fsanitize=address") #cmake -DCMAKE_BUILD_TYPE=DEBUG to add debug flags
set (CMAKE_EXPORT_COMPILE_COMMANDS ON) #vscode include path checking

# enable specific operating settings:
if(APPLE)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mac_options.cmake)
endif()

# add custom libraries:
add_subdirectory(lib/libft)

# ------------------------------------- BUILD ------------------------------------- #
# create executable from source files
add_executable(${EXEC_NAME} ${MAIN_SRCS} ${UTIL_SRCS})

# add project include to executable
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add libs to executable
target_link_libraries(${EXEC_NAME} readline termcap ft)

# ------------------------------------- TESTING ----------------------------------- #
# include gtest testing framework
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gtest.cmake)

# create executable form source files for testing
add_executable(
	minishell_tests
	test/minishell_tests.cpp
	${UTIL_SRCS}
)

# add project include to executable
target_include_directories(minishell_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add libs to executable
target_link_libraries(
	minishell_tests
	gtest_main
	gmock_main
	ft
	readline
	termcap
)

# enable ctest
gtest_discover_tests(minishell_tests)
enable_testing()
