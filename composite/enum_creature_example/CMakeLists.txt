add_executable (enum_creature_example "enum_creature_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET enum_creature_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(enum_creature_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(enum_creature_example ${Boost_LIBRARIES})
