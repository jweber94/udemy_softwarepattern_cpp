add_executable (shrink_wrapped_pimpl "shrink_wrapped_pimpl.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET shrink_wrapped_pimpl PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(shrink_wrapped_pimpl PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(shrink_wrapped_pimpl ${Boost_LIBRARIES})