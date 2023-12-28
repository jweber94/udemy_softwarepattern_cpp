add_executable (enum_state_machine "enum_state_machine.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET enum_state_machine PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(enum_state_machine PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(enum_state_machine ${Boost_LIBRARIES})