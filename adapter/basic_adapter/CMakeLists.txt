add_executable (basic_adapter "basic_adapter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic_adapter PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(basic_adapter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(basic_adapter ${Boost_LIBRARIES})