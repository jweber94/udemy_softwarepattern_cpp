add_executable (std_visit "std_visit.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET std_visit PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(std_visit PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(std_visit ${Boost_LIBRARIES})