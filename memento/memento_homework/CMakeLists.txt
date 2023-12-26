add_executable (memento_homework "memento_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET memento_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(memento_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(memento_homework ${Boost_LIBRARIES})