project(ch02_shared)

add_executable(a_stack_thread_safe a_stack_thread_safe.cc)
add_executable(b_two_lock          b_two_lock.cc)
add_executable(c_hierachy_lock     c_hierachy_lock.cc)
add_executable(d_unique_lock       d_unique_lock.cc)
add_executable(e_shared_lock       e_shared_lock.cc)
add_executable(f_recursive_lock    f_recursive_lock.cc)
