add_executable (flyweight_homework "flyweight_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET flyweight_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(flyweight_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(flyweight_homework ${Boost_LIBRARIES})