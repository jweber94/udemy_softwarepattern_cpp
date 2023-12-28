add_executable (homework_state_machine "homework_state_machine.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_state_machine PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_state_machine PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_state_machine ${Boost_LIBRARIES})