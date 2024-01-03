add_executable (classic_visitor "classic_visitor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET classic_visitor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(classic_visitor PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(classic_visitor ${Boost_LIBRARIES})