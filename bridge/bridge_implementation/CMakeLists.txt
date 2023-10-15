add_executable (bridge_implementation "bridge_implementation.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bridge_implementation PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(bridge_implementation PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(bridge_implementation ${Boost_LIBRARIES})