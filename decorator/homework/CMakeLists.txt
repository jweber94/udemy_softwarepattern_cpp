add_executable (decorator_homework "decorator_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET decorator_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(decorator_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(decorator_homework ${Boost_LIBRARIES})