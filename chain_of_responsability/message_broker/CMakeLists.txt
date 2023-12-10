add_executable (message_broker "message_broker.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET message_broker PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(message_broker PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(message_broker ${Boost_LIBRARIES})