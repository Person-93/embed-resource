include_guard ()

set (emptyFile "${CMAKE_CURRENT_BINARY_DIR}/person93.empty.c")
file (TOUCH ${emptyFile})

set (masterList "")

function (target_add_resources target)
    set (sources "")
    foreach (input ${ARGN})
        file (RELATIVE_PATH relative ${CMAKE_SOURCE_DIR}
              ${CMAKE_CURRENT_SOURCE_DIR}/${input}
              )
        set (symName "${CMAKE_BINARY_DIR}/${relative}")
        set (output ${symName}.c)
        if (NOT output IN_LIST masterList)
            message (STATUS "Adding rule to generate ${relative}")
            list (APPEND masterList ${output})
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
    add_library (${name} STATIC ${emptyFile})
    target_include_directories (${name} INTERFACE ../include)
    target_add_resources (${name} ${ARGN})
endfunction ()
