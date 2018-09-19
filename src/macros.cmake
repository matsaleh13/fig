
macro(debug_boilerplate)
    debug_message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
    debug_message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
    debug_message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
    debug_message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
endmacro(debug_boilerplate)

macro(debug_message msg)
    set(DBG_LABEL "DBG (${PROJECT_NAME})")
    message ("${DBG_LABEL}: ${msg}")
endmacro(debug_message)