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
	src/parser/combine_tokens.c
	src/executor/executor.c
	src/executor/builtins/cd.c
	src/executor/builtins/echo.c
	src/executor/builtins/env.c
	src/executor/builtins/exit.c
	src/executor/builtins/export.c
	src/executor/builtins/pwd.c
	src/executor/builtins/unset.c
	src/executor/builtins/builtin_utils.c
	src/executor/single_cmd.c
	src/executor/multiple_cmd.c
	src/executor/exec_multiple_cmd.c
	src/executor/open_files.c
	src/executor/heredoc.c
	src/executor/utils.c
	src/environment/ft_getenv.c
	src/environment/ft_environ.c
	src/environment/ft_unsetenv.c
	src/environment/ft_setenv.c
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
