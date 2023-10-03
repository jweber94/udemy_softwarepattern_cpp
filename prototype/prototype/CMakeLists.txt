add_executable (basic_prototype "prototype.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic_prototype PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(basic_prototype PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(basic_prototype ${Boost_LIBRARIES})