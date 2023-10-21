add_executable (observer_homework "observer_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET observer_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(observer_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(observer_homework ${Boost_LIBRARIES})