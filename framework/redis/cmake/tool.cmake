# 拷贝 DLL
# @TGT 目标名称
# @... 动态库名
function(copy_dll TGT)
  # 拷贝库文件
  foreach (LIBS ${ARGN})
    add_custom_command(TARGET ${TGT} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_FILE:${LIBS}>
      $<TARGET_FILE_DIR:${TGT}>
    )
  endforeach()
endfunction()

# 部署
function(deploy TGT)
  add_custom_command(TARGET ${TGT} POST_BUILD COMMAND
    "windeployqt-qt6" $<TARGET_FILE:${TGT}>)
endfunction()