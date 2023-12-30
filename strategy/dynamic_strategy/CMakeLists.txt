add_executable (dynamic_strategy "dynamic_strategy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dynamic_strategy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(dynamic_strategy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dynamic_strategy ${Boost_LIBRARIES})