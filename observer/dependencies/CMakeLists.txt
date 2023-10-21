add_executable (observer_and_dependencies "dependencies.cpp" "Observer.hpp" "Observable.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET observer_and_dependencies PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(observer_and_dependencies PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(observer_and_dependencies ${Boost_LIBRARIES})