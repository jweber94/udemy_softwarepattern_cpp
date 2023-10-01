add_executable (inner_factory "inner_factory.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET inner_factory PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(inner_factory PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(inner_factory ${Boost_LIBRARIES})