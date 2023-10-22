add_executable (composite_geometric_example "composite_geometric_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET composite_geometric_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(composite_geometric_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(composite_geometric_example ${Boost_LIBRARIES})
