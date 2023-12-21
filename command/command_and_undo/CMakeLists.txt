add_executable (command_and_undo "command_and_undo.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET command_and_undo PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(command_and_undo PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(command_and_undo ${Boost_LIBRARIES})