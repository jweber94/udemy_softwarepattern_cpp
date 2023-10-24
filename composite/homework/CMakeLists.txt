add_executable (composite_homework "composite_homework.cpp" "exercise.cpp" "exercise.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET composite_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(composite_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(composite_homework ${Boost_LIBRARIES})
