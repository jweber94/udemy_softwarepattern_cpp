add_executable (homework_interpreter "homework_interpreter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET homework_interpreter PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(homework_interpreter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(homework_interpreter ${Boost_LIBRARIES})