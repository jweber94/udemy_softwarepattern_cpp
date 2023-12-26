add_executable (memento_example "memento_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET memento_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(memento_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(memento_example ${Boost_LIBRARIES})