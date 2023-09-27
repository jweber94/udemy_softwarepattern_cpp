# good
add_executable (basic_builder "basic_builder.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic_builder PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(basic_builder PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(basic_builder ${Boost_LIBRARIES})

# bad
add_executable (bad_builder_example "bad_builder_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bad_builder_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(bad_builder_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(bad_builder_example ${Boost_LIBRARIES})