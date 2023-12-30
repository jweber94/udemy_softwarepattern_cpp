add_executable (homework_strategy "homework_strategy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_strategy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_strategy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_strategy ${Boost_LIBRARIES})