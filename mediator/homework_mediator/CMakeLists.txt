add_executable (homework_mediator "homework_mediator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_mediator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_mediator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_mediator ${Boost_LIBRARIES})