add_executable (observer_and_observable "observer_and_observable.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET observer_and_observable PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(observer_and_observable PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(observer_and_observable ${Boost_LIBRARIES})