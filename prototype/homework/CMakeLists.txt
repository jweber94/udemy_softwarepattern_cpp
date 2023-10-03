add_executable (prototype_homework "prototype_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET prototype_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(prototype_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(prototype_homework ${Boost_LIBRARIES})