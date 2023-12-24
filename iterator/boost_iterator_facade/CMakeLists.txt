add_executable (boost_iterator "boost_iterator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET boost_iterator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(boost_iterator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(boost_iterator ${Boost_LIBRARIES})