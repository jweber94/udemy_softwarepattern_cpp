add_executable (boost_flyweight "boost_flyweight.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET boost_flyweight PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(boost_flyweight PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(boost_flyweight ${Boost_LIBRARIES})