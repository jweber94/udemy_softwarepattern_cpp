add_executable (composite_command "composite_command.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET composite_command PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(composite_command PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(composite_command ${Boost_LIBRARIES})