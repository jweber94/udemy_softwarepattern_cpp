add_executable (handmade_interpreter "handmade_interpreter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic_factory PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(handmade_interpreter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(handmade_interpreter ${Boost_LIBRARIES})