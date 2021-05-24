#[==============================================================================================[.rst:
Embed Resources
---------------

Commands to embed resources at build time.

#]==============================================================================================]

include_guard ()

set (RESOURCE_empty_file "${CMAKE_CURRENT_BINARY_DIR}/person93.empty.c")
file (TOUCH ${RESOURCE_empty_file})

set (RESOURCE_master_list "")

#[==============================================================================================[.rst:

.. cmake:command:: target_add_resources

  .. code-block:: cmake

    target_add_resources(<target> <resource_file> ...)

  Embed resources in an existing target. The resource include directory is added as a private include.

#]==============================================================================================]
function (target_add_resources target)
    set (sources "")
    foreach (input ${ARGN})
        file (RELATIVE_PATH relative ${CMAKE_SOURCE_DIR}
              ${CMAKE_CURRENT_SOURCE_DIR}/${input}
              )
        set (symName "${CMAKE_BINARY_DIR}/${relative}")
        set (output ${symName}.c)
        if (NOT output IN_LIST RESOURCE_master_list)
            message (VERBOSE "Adding rule to generate ${relative}")
            list (APPEND RESOURCE_master_list ${output})
            add_custom_command (
                OUTPUT ${output}
                COMMAND person93_embed_resource ${symName} ${input}
                MAIN_DEPENDENCY ${input}
                DEPENDS person93_embed_resource
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Building binary file for embedding ${input}"
                VERBATIM
                )
        endif ()
        list (APPEND sources "${output}")
    endforeach ()
    target_sources (${target} PRIVATE ${sources})
    target_include_directories (
        ${target} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../include
        )
endfunction ()

#[==============================================================================================[.rst:

.. cmake:command:: add_resource_library

  .. code-block:: cmake

    add_resource_library(<name> <resource_file> ...)

  Create a new static library target with the given name and adds the resource files to it.
  The resource include directory is added as an interface include.

#]==============================================================================================]
function (add_resource_library name)
    message (VERBOSE "Adding resource library ${name}")
    add_library (${name} STATIC ${RESOURCE_empty_file})
    target_include_directories (
        ${name} INTERFACE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../include
        )
    target_add_resources (${name} ${ARGN})
endfunction ()
