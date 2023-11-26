add_executable (virtual_proxy "virtual_proxy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET virtual_proxy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(virtual_proxy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(virtual_proxy ${Boost_LIBRARIES})