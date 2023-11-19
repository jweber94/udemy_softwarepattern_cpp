add_executable (handmade_flyweight "handmade_flyweight.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET handmade_flyweight PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(handmade_flyweight PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(handmade_flyweight ${Boost_LIBRARIES})