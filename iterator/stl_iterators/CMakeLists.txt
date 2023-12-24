add_executable (stl_iterators "stl_iterators.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET stl_iterators PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(stl_iterators PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(stl_iterators ${Boost_LIBRARIES})