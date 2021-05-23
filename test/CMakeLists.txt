include (Person93AddResources)

# copy the samples to the build tree so the test executables can check them
unset (samples)
list (APPEND samples sample1.txt sample-2.txt dir/sample3.txt)
set (RESOURCE_sample_outputs "")
foreach (sample ${samples})
    set (RESOURCE_input ${CMAKE_CURRENT_SOURCE_DIR}/${sample})
    set (RESOURCE_output ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    list (APPEND RESOURCE_sample_outputs ${RESOURCE_output})
    # cmake-format: off
    add_custom_command (
        OUTPUT ${output}
        COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCE_input} ${RESOURCE_output}
        MAIN_DEPENDENCY ${input}
        COMMENT "Copying sample: ${RESOURCE_sample}" VERBATIM
        )
    # cmake-format: on
endforeach ()
add_custom_target (
    copy_samples DEPENDS ${RESOURCE_sample_outputs} COMMENT "Copying samples"
    )

add_resource_library (testing_common ${samples})
target_link_libraries (testing_common INTERFACE std::filesystem)
add_dependencies (testing_common copy_samples)

add_executable (simple main.cpp)
target_link_libraries (simple PRIVATE testing_common)

add_test (simple simple)
