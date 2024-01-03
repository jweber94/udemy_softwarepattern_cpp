add_executable (intrusive_visitor "intrusive_visitor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET intrusive_visitor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(intrusive_visitor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(intrusive_visitor ${Boost_LIBRARIES})