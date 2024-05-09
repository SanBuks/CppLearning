set(x 1)
set(y 3)


block(PROPAGATE x y)
  set(x 2)
  unset(y)
  # 结束会将 x y 的改变投递到父作用域中
endblock()

# x has the value 2 here
message(STATUS ${x})
# y is no longer defined
message(STATUS ${y})
