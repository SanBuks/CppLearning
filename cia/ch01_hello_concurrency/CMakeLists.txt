project(ch01_hello_concurrency)

add_executable(a_hello_by_func     a_hello_by_func.cc)
add_executable(b_hello_by_operator b_hello_by_operator.cc)
add_executable(c_hello_by_lambda   c_hello_by_lambda.cc)
add_executable(d_catch_exception   d_catch_exception.cc)
add_executable(e_thread_guard      e_thread_guard.cc)
add_executable(f_avoid_implicit    f_avoid_implicit.cc)
add_executable(g_ref_arg           g_ref_arg.cc)
