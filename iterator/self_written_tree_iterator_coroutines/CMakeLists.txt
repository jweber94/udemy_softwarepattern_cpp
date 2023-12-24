add_executable (self_written_tree_iterator_coroutines "self_written_tree_iterator_coroutines.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET self_written_tree_iterator_coroutines PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(self_written_tree_iterator_coroutines PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(self_written_tree_iterator_coroutines ${Boost_LIBRARIES})