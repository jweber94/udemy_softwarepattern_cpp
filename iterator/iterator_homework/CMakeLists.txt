add_executable (iterator_homework "iterator_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET iterator_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(iterator_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(iterator_homework ${Boost_LIBRARIES})