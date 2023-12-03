add_executable (temperaturPropertyProxy "temperaturPropertyProxy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET temperaturPropertyProxy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(temperaturPropertyProxy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(temperaturPropertyProxy ${Boost_LIBRARIES})