add_executable (observer_with_boost "observer_with_boost.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET observer_with_boost PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(observer_with_boost PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(observer_with_boost ${Boost_LIBRARIES})