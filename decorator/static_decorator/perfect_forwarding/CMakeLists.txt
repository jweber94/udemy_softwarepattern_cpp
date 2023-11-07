# concepts
add_executable (perfect_forwarding "perfect_forwarding.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET perfect_forwarding PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(perfect_forwarding PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(perfect_forwarding ${Boost_LIBRARIES})