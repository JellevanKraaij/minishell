add_library(readline STATIC IMPORTED)
set_property(TARGET readline APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(readline PROPERTIES IMPORTED_LOCATION_NOCONFIG "/usr/local/opt/readline/lib/libreadline.a")
target_include_directories(readline INTERFACE "/usr/local/Cellar/readline/8.1.2/include")
