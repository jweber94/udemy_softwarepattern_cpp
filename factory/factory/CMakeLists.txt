add_executable (basic_factory "factory.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic_factory PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(basic_factory PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(basic_factory ${Boost_LIBRARIES})