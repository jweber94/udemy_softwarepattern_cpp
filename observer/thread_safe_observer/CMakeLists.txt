add_executable (thread_safe_observer "thread_safe_observer.cpp" "Observable.hpp" "Observer.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET thread_safe_observer PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(thread_safe_observer PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(thread_safe_observer ${Boost_LIBRARIES})