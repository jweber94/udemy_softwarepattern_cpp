add_executable (multimethods "multimethods.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET multimethods PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(multimethods PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(multimethods ${Boost_LIBRARIES})