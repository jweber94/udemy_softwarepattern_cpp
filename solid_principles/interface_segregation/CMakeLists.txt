add_executable (interface_segregation_good "interface_segregation_good.cpp" )
add_executable (interface_segregation_bad "interface_segregation_bad.cpp" )

# good
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET interface_segregation_good PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(interface_segregation_good PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interface_segregation_good ${Boost_LIBRARIES})

# bad
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET interface_segregation_bad PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(interface_segregation_bad PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interface_segregation_bad ${Boost_LIBRARIES})