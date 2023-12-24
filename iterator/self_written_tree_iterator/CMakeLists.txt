add_executable (self_written_tree_iterator "self_written_tree_iterator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET self_written_tree_iterator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(self_written_tree_iterator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(self_written_tree_iterator ${Boost_LIBRARIES})