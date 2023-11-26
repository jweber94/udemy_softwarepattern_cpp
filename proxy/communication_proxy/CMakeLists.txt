add_executable (communication_proxy "communication_proxy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET communication_proxy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(communication_proxy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(communication_proxy ${Boost_LIBRARIES})