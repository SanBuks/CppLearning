add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_FUNCTION})
install(FILES common.h DESTINATION include)