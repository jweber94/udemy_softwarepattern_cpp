add_executable (serialization_prototype "serialization_prototype.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET serialization_prototype PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(serialization_prototype PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(serialization_prototype ${Boost_LIBRARIES})