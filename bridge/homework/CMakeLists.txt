add_executable (bridge_homework "bridge_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bridge_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(bridge_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(bridge_homework ${Boost_LIBRARIES})