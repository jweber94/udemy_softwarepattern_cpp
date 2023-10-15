add_executable (caching_adapter "caching_adapter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET caching_adapter PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(caching_adapter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(caching_adapter ${Boost_LIBRARIES})