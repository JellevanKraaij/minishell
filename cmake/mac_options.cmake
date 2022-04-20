add_library(readline STATIC IMPORTED)
set_property(TARGET readline APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(readline PROPERTIES IMPORTED_LOCATION_NOCONFIG "$ENV{HOME}/.brew/opt/readline/lib/libreadline.a")
target_include_directories(readline INTERFACE "$ENV{HOME}/.brew/opt/readline/include")
