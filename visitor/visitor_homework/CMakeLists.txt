add_executable (visitor_homework "visitor_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET visitor_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(visitor_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(visitor_homework ${Boost_LIBRARIES})