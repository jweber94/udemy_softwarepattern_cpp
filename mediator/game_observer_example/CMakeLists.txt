add_executable (game_mediator_example "game_mediator_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET game_mediator_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(game_mediator_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(game_mediator_example ${Boost_LIBRARIES})