add_executable (template_pattern_example "template_pattern_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET template_pattern_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(template_pattern_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(template_pattern_example ${Boost_LIBRARIES})