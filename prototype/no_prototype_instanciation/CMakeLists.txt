add_executable (no_prototype_employee_example "employee_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET no_prototype_employee_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(no_prototype_employee_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(no_prototype_employee_example ${Boost_LIBRARIES})