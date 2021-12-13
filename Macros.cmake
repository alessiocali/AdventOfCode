macro (add_copy_input_command TargetName InputFile)
    add_custom_command(
        TARGET ${TargetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/${TargetName}/${InputFile}
        ${CMAKE_CURRENT_BINARY_DIR}/${InputFile}
    )
endmacro()