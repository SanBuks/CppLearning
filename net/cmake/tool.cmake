# 部署对象依赖动态库
function(install_dlls TGT)
  add_custom_command(TARGET ${TGT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:${TGT}>
    $<TARGET_FILE_DIR:${TGT}>
    COMMAND_EXPAND_LISTS
  )
endfunction()
