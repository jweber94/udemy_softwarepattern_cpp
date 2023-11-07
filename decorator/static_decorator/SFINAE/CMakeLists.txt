# sfinae class
add_executable (sfinae "sfinae.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sfinae PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(sfinae PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(sfinae ${Boost_LIBRARIES})