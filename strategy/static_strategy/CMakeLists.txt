add_executable (static_strategy "static_strategy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET static_strategy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(static_strategy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(static_strategy ${Boost_LIBRARIES})