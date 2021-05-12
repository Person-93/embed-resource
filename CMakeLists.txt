cmake_minimum_required ( VERSION 3.5 )
project ( EmbedResource )

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

option ( PERSON93_RESOURCE_ENABLE_TESTING OFF )
list ( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

find_package ( Filesystem REQUIRED )

add_subdirectory ( src )
