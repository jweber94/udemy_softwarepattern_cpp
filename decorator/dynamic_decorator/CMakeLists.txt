add_executable (dynamic_decorator "dynamic_decorator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dynamic_decorator PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(dynamic_decorator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(dynamic_decorator ${Boost_LIBRARIES})