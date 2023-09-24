add_executable (dependency_inversion_good "dependency_inversion_good.cpp" )
add_executable (dependency_inversion_bad "dependency_inversion_bad.cpp" )

# good
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dependency_inversion_good PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(dependency_inversion_good PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dependency_inversion_good ${Boost_LIBRARIES})

# bad
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dependency_inversion_bad PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(dependency_inversion_bad PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dependency_inversion_bad ${Boost_LIBRARIES})