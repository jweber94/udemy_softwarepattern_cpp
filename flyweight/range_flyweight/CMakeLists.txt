add_executable (range_flyweight "range_flyweight.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET range_flyweight PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(range_flyweight PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(range_flyweight ${Boost_LIBRARIES})