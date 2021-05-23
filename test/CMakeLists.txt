include (Person93AddResources)

# copy the samples to the build tree so the test executables can check them
list (APPEND samples sample1.txt sample-2.txt dir/sample3.txt)
set (sampleOutputs "")
foreach (sample ${samples})
    set (input ${CMAKE_CURRENT_SOURCE_DIR}/${sample})
    set (output ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    list (APPEND sampleOutputs ${output})
    add_custom_command (
        OUTPUT ${output} COMMAND ${CMAKE_COMMAND} -E copy ${input} ${output}
        MAIN_DEPENDENCY ${input} COMMENT "Copying sample: ${sample}" VERBATIM
        )
endforeach ()
add_custom_target (copy_samples DEPENDS ${sampleOutputs})

add_resource_library (testing_common ${samples})
target_link_libraries (testing_common INTERFACE std::filesystem)
add_dependencies (testing_common copy_samples)

add_executable (simple main.cpp)
target_link_libraries (simple PRIVATE testing_common)

add_test (simple simple)
