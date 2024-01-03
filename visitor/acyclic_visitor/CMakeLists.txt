add_executable (acyclic_visitor "acyclic_visitor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET acyclic_visitor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(acyclic_visitor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(acyclic_visitor ${Boost_LIBRARIES})