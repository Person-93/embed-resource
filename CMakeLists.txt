cmake_minimum_required (VERSION 3.5)
project (EmbedResource)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

option (PERSON93_RESOURCE_REGISTER_COMPILATION_DB OFF)
option (PERSON93_RESOURCE_ENABLE_TESTING OFF)
option (PERSON93_RESOURCE_BUILD_DOCS OFF)
if (PERSON93_RESOURCE_ENABLE_TESTING)
    set (PERSON93_RESOURCE_REGISTER_COMPILATION_DB ON CACHE BOOL "" FORCE)
endif ()

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (PERSON93_RESOURCE_REGISTER_COMPILATION_DB)
    set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
    file (WRITE ${PROJECT_BINARY_DIR}/register_compilation_db.cmake
          "file(WRITE ${PROJECT_SOURCE_DIR}/build-dir.txt ${PROJECT_BINARY_DIR})"
          )
    add_custom_target (
        register_compilation_db
        COMMAND ${CMAKE_COMMAND} -P
                ${CMAKE_CURRENT_BINARY_DIR}/register_compilation_db.cmake
        COMMENT "Registering compilation database"
        )
endif ()

add_subdirectory (vendor)
find_package (Filesystem REQUIRED)

add_subdirectory (src)
include (Person93AddResources)

if (PERSON93_RESOURCE_ENABLE_TESTING)
    include (CTest)
    add_subdirectory (test)
    # cmake-format: off
    set_property (DIRECTORY test PROPERTY EXCLUDE_FROM_ALL ON)
    # cmake-format: on
    configure_file (
        cmake/CTestCustom.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CTestCustom.cmake"
        @ONLY
        )
endif ()

if (PERSON93_RESOURCE_BUILD_DOCS)
    find_package (Sphinx REQUIRED)
    add_subdirectory (docs)
    set_property (DIRECTORY docs PROPERTY EXCLUDE_FROM_ALL ON)
endif ()
