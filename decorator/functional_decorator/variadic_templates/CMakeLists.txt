add_executable (variadic_templates "variadic_templates.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET variadic_templates PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(variadic_templates PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(variadic_templates ${Boost_LIBRARIES})