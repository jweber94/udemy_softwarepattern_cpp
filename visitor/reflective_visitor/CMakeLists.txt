add_executable (reflective_visitor "reflective_visitor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET reflective_visitor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(reflective_visitor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(reflective_visitor ${Boost_LIBRARIES})