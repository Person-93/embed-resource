include_guard ()

set (RESOURCE_empty_file "${CMAKE_CURRENT_BINARY_DIR}/person93.empty.c")
file (TOUCH ${RESOURCE_empty_file})

set (RESOURCE_master_list "")

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
    target_include_directories (${target} PRIVATE ../include)
endfunction ()

function (add_resource_library name)
    message (VERBOSE "Adding resource library ${name}")
    add_library (${name} STATIC ${RESOURCE_empty_file})
    target_include_directories (${name} INTERFACE ../include)
    target_add_resources (${name} ${ARGN})
endfunction ()
