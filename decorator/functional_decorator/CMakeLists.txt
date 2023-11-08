add_executable (functional_decorator "functional_decorator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET functional_decorator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(functional_decorator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(functional_decorator ${Boost_LIBRARIES})

add_subdirectory("variadic_templates")