add_executable (homework_adapter "homework_adapter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_adapter PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_adapter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_adapter ${Boost_LIBRARIES})