add_executable (array_backed_properties "array_backed_properties.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET array_backed_properties PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(array_backed_properties PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(array_backed_properties ${Boost_LIBRARIES})
