set(Var normal)
set(Var cache CACHE STRING "" FORCE)
message(STATUS "Var is ${Var}")
unset(Var)
message(STATUS "Var is ${Var}")

set(Opt TRUE)
option(Opt "" OFF)
message(STATUS "Opt is ${Opt}")
