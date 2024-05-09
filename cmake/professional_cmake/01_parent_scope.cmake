set(x 1)
set(y 3)

block()
  # 改变了父作用域中的变量
  set(x 2 PARENT_SCOPE)
  # 改变了父作用域中的变量
  unset(y PARENT_SCOPE)

  # x still has the value 1 here
  message(STATUS ${x})
  # y still exists and has the value 3
  message(STATUS ${y})
endblock()

# x has the value 2 here
message(STATUS ${x})
# y is no longer defined
message(STATUS ${y})
